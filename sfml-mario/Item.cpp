#include "stdafx.h"
#include "Item.h"
#include "GroundTileMap.h"
#include "SceneDev2.h"
#include "Block.h"

Item::Item(const std::string& name)
	: GameObject(name)
{
}

Item::Item(const std::string& name, ItemType item)
	: GameObject(name), itemType(item)
{
}

void Item::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	item.setPosition(pos);
}

void Item::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	item.setRotation(rot);
}

void Item::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	item.setScale(s);
}

void Item::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	item.setOrigin(o);
}

void Item::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(item, preset);
	}
}

void Item::Init()
{
	animator.SetTarget(&item);
}

void Item::Release()
{
}

void Item::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetOrigin(Origins::TL);
	SetScale({ 0.8f, 0.8f });

	if (itemType == ItemType::Mushroom)
	{
		animator.Play("animations/mushroom.csv");
	}
	if (itemType == ItemType::Coin)
	{
		animator.Play("animations/coin.csv");
	}

	isGrounded = true;
	speed = 80.f;
	activeMushroom = false;

}

void Item::Update(float dt)
{
	animator.Update(dt);

	if (itemType == ItemType::Mushroom && activeMushroom)
	{
		velocity.x = speed;
		position += velocity * dt;

		if (!isGrounded)
		{
			velocity += gravity * dt;
		}

		isWallCheckMushroom();
		isBlockCheckMushroom();
		isGroundedCheckMushroom();
	}

	SetPosition(position);

}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
}

void Item::startItemUp()
{
}

void Item::isGroundedCheckMushroom()
{
	if (!ground)
	{
		return;
	}

	sf::FloatRect hitBox = item.getGlobalBounds();

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
				position.y = 390.f;
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

void Item::isWallCheckMushroom()
{
	if (!ground)
	{
		return;
	}

	if (velocity.x > 0)
	{
		sf::FloatRect hitBox = GetHitBoxMushroom();
		if (ground->IsWallAt({ hitBox.left + hitBox.width, hitBox.top + hitBox.height / 2 }))
		{
			speed = -speed;
		}
	}
	else if (velocity.x < 0)
	{
		sf::FloatRect hitBox = GetHitBoxMushroom();
		if (ground->IsWallAt({ hitBox.left, hitBox.top + hitBox.height / 2 }))
		{
			speed = -speed;
			//velocity.x = 0;
		}
	}
}

void Item::isBlockCheckMushroom()
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

		sf::FloatRect hitBox = GetHitBoxMushroom();


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

sf::FloatRect Item::GetHitBoxMushroom() const
{
	return item.getGlobalBounds();
}
