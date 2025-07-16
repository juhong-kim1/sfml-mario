#include "stdafx.h"
#include "Block.h"
#include "Item.h"
#include "sceneDev2.h"

Block::Block(const std::string& name, BlockType type)
	:GameObject(name), blocktype(type)
{
}

void Block::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void Block::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void Block::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void Block::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void Block::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void Block::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(block, originPreset);
	}
}

void Block::Init()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 1;
}

void Block::Release()
{
}

void Block::Reset()
{
	block.setTexture(TEXTURE_MGR.Get("graphics/tiles2x.png"));

	switch (blocktype)
	{
	case BlockType::GeneralBlock:
		blockRect = {32, 0, 32, 32};
		break;
	case BlockType::QuestionBlock:
		blockRect = { 768, 0, 32, 32 };
		break;
		

	}

	block.setTextureRect(blockRect);
	block.setPosition(position);

	shakeCurrentTime = 0.0f;
	isItemUsed = false;
	isAnimateCoin = false;
	coinCurrentTime = 0.0;
	isAnimateMushroom = false;
	mushroomCurrentTime = 0.0;
	isBreakBlock = false;

	SetOrigin(Origins::TL);
	SetScale({ 1.f, 1.f });

	isShaking = false;

	SetActive(true);
}

void Block::Update(float dt)
{
	BlockShakeAnimation(dt);
	CoinReleaseAnimation(dt);
	MushroomReleaseAnimation(dt);
	BlockBreakAnimation(dt);


}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(block);
}

void Block::BlockShakeAnimation(float dt)
{
	if (!isShaking)
	{
		return;
	}

	shakeCurrentTime += dt;

	if (shakeCurrentTime < shakeMaxTime && !isItemUsed)
	{
		float shake = shakeCurrentTime / shakeMaxTime;

		if (shake < 0.25f)
		{
			block.setPosition(originPosition + sf::Vector2f(0, -4.0f));
		}
		else if (shake < 0.5f)
		{
			block.setPosition(originPosition + sf::Vector2f(0, -8.0f));
		}
		else if (shake < 0.75f)
		{
			block.setPosition(originPosition + sf::Vector2f(0, -4.0f));
		}
		else
		{
			block.setPosition(originPosition);
		}
	}
	else
	{
		isShaking = false;
		block.setPosition(originPosition);
	}

}

void Block::BlockShakeAnimationStart()
{
	isShaking = true;
	shakeCurrentTime = 0.0f;
	originPosition = position;
}

void Block::SetItem(Item* item)
{
	items = item;
}

void Block::ReleaseItem()
{
	if (items != nullptr && !items->GetActive() && !isItemUsed)
	{
			items->SetActive(true);

			if (blocktype == BlockType::QuestionBlock)
			{
				blockRect = { 864, 0, 32, 32 };
				block.setTextureRect(blockRect);
			}

			if (items->GetItemType() == ItemType::Mushroom)
			{
				MushroomReleaseAnimationStart(position);
			}
			if (items->GetItemType() == ItemType::Coin)
			{
				CoinReleaseAnimationStart(position);
			}
	}
}

void Block::CoinReleaseAnimationStart(const sf::Vector2f& pos)
{
	isAnimateCoin = true;
	coinCurrentTime = 0.0;
	originCoinPosition = pos;
}

void Block::CoinReleaseAnimation(float dt)
{
	if (!isAnimateCoin)
	{
		return;
	}

	coinCurrentTime += dt;

	if (coinCurrentTime < coinMaxTime)
	{
		float progress = coinCurrentTime / coinMaxTime;
		float offsetY = 0;

		if (progress < 0.5f)
		{
			offsetY = -(progress * 2.0f) * coinDistance;
		}
		else
		{
			offsetY = -((1.0f - progress) * 2.0f) * coinDistance;
		}

		items->SetPosition(originCoinPosition + sf::Vector2f(0, offsetY));
	}
	else
	{
		isAnimateCoin = false;
		items->SetActive(false);
		isItemUsed = true;
	}
}

void Block::MushroomReleaseAnimationStart(const sf::Vector2f& pos)
{
	isAnimateMushroom = true;
	mushroomCurrentTime = 0.0;
	originMushroomPosition = pos;
}

void Block::MushroomReleaseAnimation(float dt)
{
	if (!isAnimateMushroom)
	{
		return;
	}

	mushroomCurrentTime += dt;

	if (mushroomCurrentTime < mushroomMaxTime)
	{
		float progress = mushroomCurrentTime / mushroomMaxTime;
		float offsetY = -(progress)*mushroomDistance;
		items->SetPosition(originMushroomPosition + sf::Vector2f(0, offsetY));
	}
	else
	{
		isAnimateMushroom = false;
		sf::Vector2f finalPos = originMushroomPosition;
		finalPos.y -= mushroomDistance;
		items->SetPosition(finalPos);
		items->ActiveMushroom();
		isItemUsed = true;
	}
}

void Block::BlockBreakAnimationStart()
{
	isBreakBlock = true;
	breakSpeed = 500.f;
}

void Block::BlockBreakAnimation(float dt)
{
	if (!isBreakBlock)
	{
		return;
	}

	SetActive(false);
}
