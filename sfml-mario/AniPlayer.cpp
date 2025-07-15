#include "stdafx.h"
#include "AniPlayer.h"
#include "HitBox.h"
#include "GroundTileMap.h"
#include "SceneDev2.h"
#include "Block.h"

AniPlayer::AniPlayer(const std::string& name)
	: GameObject(name), mario(Mario::Small)
{
}

void AniPlayer::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	body.setPosition(position);
}

void AniPlayer::SetRotation(float angle)
{
	rotation = angle;
	body.setRotation(rotation);
}

void AniPlayer::SetScale(const sf::Vector2f& s)
{
	scale = s;
	body.setScale(scale);
}

void AniPlayer::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(body, originPreset);
	}
}

void AniPlayer::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(body, originPreset);
}

void AniPlayer::Init()
{
	animator.SetTarget(&body);

	body.setScale({ 1.f, 1.f });
	SetPosition({ 100.f, 416.f });
}

void AniPlayer::Release()
{
}

void AniPlayer::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	switch (mario)
	{
	case Mario::Small:
		animator.Play("animations/idle.csv");
		break;
	case Mario::Big:
		animator.Play("animations/big_idle.csv");
		break;
	}
	SetOrigin(Origins::BC);

	currentJumpTime = 0;
}

void AniPlayer::Update(float dt)
{
	animator.Update(dt);

	float h = 0.f;

	h = InputMgr::GetAxis(Axis::Horizontal);
	velocity.x = h * speed;


	//if (InputMgr::GetKey(sf::Keyboard::Space))
	//{
	//	if (currentJumpTime < maxJumpTime)
	//	{
	//		currentJumpTime += dt;
	//		isGrounded = false;
	//		velocity.y = -250.f;
	//		animator.Play("animations/jump.csv");
	//	}
	//}

	if (!isGrounded)
	{
		velocity += gravity * dt;
	}

	isWallCheck();
	isBlockCheck();

	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		auto items = scene->GetItems();
		sf::FloatRect playerBounds = body.getGlobalBounds();

		for (auto* item : items)
		{
			if (item->GetActive() && playerBounds.intersects(item->GetHitBoxMushroom()))
			{
				if (item->GetItemType() == ItemType::Mushroom && mario == Mario::Small)
				{
					mario = Mario::Big;
					animator.Play("animations/get_mushroom.csv");

					SetOrigin(Origins::BC);
				}
				item->SetActive(false);
			}
		}
	}


	position += velocity * dt;


	isGroundedCheck();

	SetPosition(position);

	if (h != 0.f)
	{
		SetScale(h > 0.f ? sf::Vector2f(1.f, 1.f) : sf::Vector2f(-1.f, 1.f));
	}

	// Ani
	switch (mario)
	{
	case Mario::Small:
		if (animator.GetCurrentClipId() == "Idle")
		{
			if (h != 0.f)
			{
				animator.Play("animations/run.csv");
			}
		}
		else if (animator.GetCurrentClipId() == "Run")
		{
			if (h > 0.f && InputMgr::GetKeyDown(sf::Keyboard::A))
			{
				animator.Play("animations/stop.csv");
			}
			if (h < 0.f && InputMgr::GetKeyDown(sf::Keyboard::D))
			{
				animator.Play("animations/stop.csv");
			}
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
			}
		}
		else if (animator.GetCurrentClipId() == "Jump" && isGrounded)
		{
			if (h == 0.f)
			{
				animator.Play("animations/idle.csv");
			}
			else
			{
				animator.Play("animations/run.csv");
			}
		}
		if (animator.GetCurrentClipId() == "Stop")
		{
			if (velocity.x < 0.3f && velocity.x > -0.3f)
			{
				animator.Play("animations/idle.csv");
			}
		}
		if (InputMgr::GetKey(sf::Keyboard::Space))
		{
			if (currentJumpTime < maxJumpTime)
			{
				currentJumpTime += dt;
				isGrounded = false;
				velocity.y = -250.f;
				animator.Play("animations/jump.csv");
			}
		}
		break;
	case Mario::Big:
		if (animator.GetCurrentClipId() == "Big_Idle")
		{
			if (h != 0.f)
			{
				animator.Play("animations/big_run.csv");
			}
		}
		else if (animator.GetCurrentClipId() == "Big_Run")
		{
			if (h > 0.f && InputMgr::GetKeyDown(sf::Keyboard::A))
			{
				animator.Play("animations/big_stop.csv");
			}
			if (h < 0.f && InputMgr::GetKeyDown(sf::Keyboard::D))
			{
				animator.Play("animations/big_stop.csv");
			}
			if (h == 0.f)
			{
				animator.Play("animations/big_idle.csv");
			}
		}
		else if (animator.GetCurrentClipId() == "Big_Jump" && isGrounded)
		{
			if (h == 0.f)
			{
				animator.Play("animations/big_idle.csv");
			}
			else
			{
				animator.Play("animations/big_run.csv");
			}
		}
		if (animator.GetCurrentClipId() == "Big_Stop")
		{
			if (velocity.x < 0.3f && velocity.x > -0.3f)
			{
				animator.Play("animations/big_idle.csv");
			}
		} 
		if (InputMgr::GetKey(sf::Keyboard::Space))
		{
			if (currentJumpTime < maxJumpTime)
			{
				currentJumpTime += dt;
				isGrounded = false;
				velocity.y = -250.f;
				animator.Play("animations/big_jump.csv");
			}
		}
		if (InputMgr::GetKey(sf::Keyboard::S))
		{
			//speed 변경해야할듯?
			animator.Play("animations/big_sitdown.csv");
		}
		break;
	}

	hitBox.UpdateTransform(body, body.getLocalBounds());
}

void AniPlayer::Draw(sf::RenderWindow& window)
{
	window.draw(body);
	hitBox.Draw(window);
}

sf::FloatRect AniPlayer::GetHitBoxBottom() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left + 4.f, globalBounds.top + globalBounds.height - 4.f, globalBounds.width - 8.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxTop() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	return sf::FloatRect(globalBounds.left + 2.f, globalBounds.top, globalBounds.width - 4.f, 4.f);
}

sf::FloatRect AniPlayer::GetHitBoxLeft() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	if (mario == Mario::Small)
	{
		return sf::FloatRect(globalBounds.left, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
	}
	else
	{
		return sf::FloatRect(globalBounds.left, globalBounds.top + 4.f, 6.f, globalBounds.height - 8.f);
	}
}

sf::FloatRect AniPlayer::GetHitBoxRight() const
{
	sf::FloatRect globalBounds = body.getGlobalBounds();
	if (mario == Mario::Small)
	{
		return sf::FloatRect(globalBounds.left + globalBounds.width - 4.f, globalBounds.top + 2.f, 4.f, globalBounds.height - 4.f);
	}
	else
	{
		return sf::FloatRect(globalBounds.left + globalBounds.width - 8.f, globalBounds.top + 4.f, 6.f, globalBounds.height - 8.f);
	}

}

void AniPlayer::isGroundedCheck()
{
	if (!ground)
	{
		return;
	}

	sf::FloatRect bottomBox = GetHitBoxBottom();

	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (scene)
	{
		auto blocks = scene->GetBlocks();

		for (auto* block : blocks)
		{
			sf::FloatRect blockBounds = block->GetGlobalBounds();
			if (bottomBox.intersects(blockBounds))
			{
				return;
			}
		}
	}

	if (velocity.y >= 0)
	{
		bool foundGround = false;

		for (float i = bottomBox.left; i < bottomBox.left + bottomBox.width; ++i)
		{
			if (ground->IsGroundAt({ i, bottomBox.top + bottomBox.height }))
			{
				
				int tileY = static_cast<int>((bottomBox.top + bottomBox.height) / 32.f);
				float tileTopY = tileY * 32.f;
				position.y = tileTopY;
				velocity.y = 0;
				isGrounded = true;
				currentJumpTime = 0;
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

void AniPlayer::isWallCheck()
{
	if (!ground)
	{
		return;
	}

	if (velocity.x > 0)
	{
		sf::FloatRect rightBox = GetHitBoxRight();
		for (float y = rightBox.top; y < rightBox.top + rightBox.height; y += 8.f)
		{
			if (ground->IsWallAt({ rightBox.left + rightBox.width, y }))
			{
				velocity.x = 0;
				return;
			}
		}
	}
	else if (velocity.x < 0)
	{
		sf::FloatRect leftBox = GetHitBoxLeft();
		for (float y = leftBox.top; y < leftBox.top + leftBox.height; y += 8.f)
		{
			if (ground->IsWallAt({ leftBox.left, y }))
			{
				velocity.x = 0;
				return;
			}
		}
	}
}

void AniPlayer::isBlockCheck()
{
	SceneDev2* scene = dynamic_cast<SceneDev2*>(SCENE_MGR.GetCurrentScene());
	if (!scene)
	{
		return;
	}

	auto blocks = scene->GetBlocks();

	for (auto* block : blocks)
	{
		sf::FloatRect blockBounds = block->GetGlobalBounds();

		sf::FloatRect bottomBox = GetHitBoxBottom();
		sf::FloatRect topBox = GetHitBoxTop();
		sf::FloatRect leftBox = GetHitBoxLeft();
		sf::FloatRect rightBox = GetHitBoxRight();

		if (velocity.y > 0 && bottomBox.intersects(blockBounds))
		{
			//position.y = blockBounds.top;

			velocity.y = 0;
			isGrounded = true;
			currentJumpTime = 0;
			return;
		}
		if (velocity.y < 0 && topBox.intersects(blockBounds) && position.x > blockBounds.left - 4.f && position.x < blockBounds.left + blockBounds.width + 4.f)
		{
			if (!block->IsShaking())
			{
				velocity.y = 0;
				currentJumpTime = maxJumpTime;
				block->BlockShakeAnimationStart();
				block->ReleaseItem();
				return;
			}
		}
		if (velocity.x > 0 && rightBox.intersects(blockBounds))
		{
			velocity.x = 0;
			return;
		}
		if (velocity.x < 0 && leftBox.intersects(blockBounds))
		{
			velocity.x = 0;
			return;
		}
	}
}

//void AniPlayer::MarioGetMushroom()
//{
//	animator.Play("animations/get_mushroom.csv");
//	mario = Mario::Big;
//}
