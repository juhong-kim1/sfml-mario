#include "stdafx.h"
#include "Enemy.h"
#include "HitBox.h"
#include "SceneDev2.h"
#include "Block.h"
#include "GroundTileMap.h"
#include "UiHud.h"

Enemy::Enemy(const std::string& name, float x, float y)
	:GameObject(name), positionX(x), positionY(y)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Enemy::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Enemy::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Enemy::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Enemy::Init()
{
	animator.SetTarget(&body);

	//body.setScale({ 1.f, 1.f });
	//SetPosition({ positionX, positionY });
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	//SetOrigin(Origins::BC);

	body.setScale({ 1.f, 1.f });
	SetPosition({ positionX, positionY });

	SetOrigin(Origins::BC);

	animator.Play("animations/goomba_move.csv");

	isDying = false;
	deathCurrentTimer = 0.0f;
	velocity = { 0.f, 0.f };
	isGrounded = true;
	speed = -80.f;
	isDyingOnTop = false;
	dyingCurrentTimer = 0.0f;
}

void Enemy::Update(float dt)
{
	//if (!GetActive())
	//{
	//	return;
	//}

	if (isDyingOnTop)
	{
		animator.Update(dt);
		dyingCurrentTimer += dt;

		if (dyingCurrentTimer < 0.3f)
		{
			velocity.y = -100.f;
		}
		else
		{
			velocity.y += gravity.y * dt;
		}

		position += velocity * dt;
		SetPosition(position);
		SetScale({ 1.f,-1.f });

		if (dyingCurrentTimer >= dyingTimer)
		{
			SetActive(false);
		}
		return;
	}

	if (body.getPosition().y >= 500.f)
	{
		isDying = true;
	}
	if (isDying)
	{
		animator.Update(dt);
		deathCurrentTimer += dt;

		if (deathCurrentTimer >= deathTimer)
		{
			SetActive(false);
		}
		
		return;
	}

	animator.Update(dt);
	velocity.x = speed;
	position += velocity * dt;

	if (!isGrounded)
	{
		velocity += gravity * dt;
	}

	isWallCheckEnemy();
	isBlockCheckEnemy();
	isGroundedCheckEnemy();

	SetPosition(position);

	hitBox.UpdateTransform(body, body.getLocalBounds());
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

void Enemy::isGroundedCheckEnemy()
{
	if (!ground)
	{
		return;
	}

	sf::FloatRect hitBox = body.getGlobalBounds();

	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		auto blocks = scene->GetBlocks();

		for (auto* block : blocks)
		{
			sf::FloatRect blockBounds = block->GetGlobalBounds();
			if (hitBox.intersects(blockBounds))
			{
				return;
			}
		}
	}

	if (velocity.y >= 0)
	{
		bool foundGround = false;

		for (float i = hitBox.left; i < hitBox.left + hitBox.width; ++i)
		{
			if (ground->IsGroundAt({ i, hitBox.top + hitBox.height }))
			{
				//position.y = 380.f;
				velocity.y = 0;
				isGrounded = true;
				foundGround = true;
				return;
			}
		}
		if (!foundGround)
		{
			isGrounded = false;
		}
	}

}

void Enemy::isWallCheckEnemy()
{
	if (!ground)
	{
		return;
	}

	if (velocity.x > 0)
	{
		sf::FloatRect hitBox = GetHitBoxEnemy();
		if (ground->IsWallAt({ hitBox.left + hitBox.width, hitBox.top + hitBox.height / 2 }))
		{
			speed = -speed;
		}
	}
	else if (velocity.x < 0)
	{
		sf::FloatRect hitBox = GetHitBoxEnemy();
		if (ground->IsWallAt({ hitBox.left, hitBox.top + hitBox.height / 2 }))
		{
			speed = -speed;
			//velocity.x = 0;
		}
	}
}

void Enemy::isBlockCheckEnemy()
{
	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{return;}

	auto blocks = scene->GetBlocks();

	for (auto* block : blocks)
	{
		sf::FloatRect blockBounds = block->GetGlobalBounds();

		sf::FloatRect hitBox = GetHitBoxEnemy();


		if (velocity.y > 0 && hitBox.intersects(blockBounds))
		{
			//position.y = blockBounds.top;
			velocity.y = 0;
			isGrounded = true;
			return;
		}
		if (velocity.x > 0 && hitBox.intersects(blockBounds))
		{
			velocity.x = 0;
			return;
		}
		if (velocity.x < 0 && hitBox.intersects(blockBounds))
		{
			velocity.x = 0;
			return;
		}

	}
}

void Enemy::Die()
{
	if (!isDying)
	{
		isDying = true;
		deathCurrentTimer = 0.0f;
		animator.Play("animations/goomba_die.csv");
		velocity.x = 0;
	}
}

void Enemy::DyingOnTop()
{
	if (!isDyingOnTop)
	{
		isDyingOnTop = true;
		dyingCurrentTimer = 0.0f;
		velocity = { 0.f, -200.f };
		uiHud->AddScore(100);
	}

}

sf::FloatRect Enemy::GetHitBoxEnemy() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left + 4.0f ,globalBounds.top + 8.0f,globalBounds.width -4.0f,globalBounds.height - 8.0f);
}

