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

	SetOrigin(Origins::TL);
	SetScale({ 1.f, 1.f });
}

void Block::Update(float dt)
{
	BlockShakeAnimation(dt);
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

	if (shakeCurrentTime < shakeMaxTime)
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
	if (items != nullptr && !items->GetActive())
	{
			items->SetActive(true);

			sf::Vector2f newPos = position;
			newPos.y -= 32.f;
			newPos.x += 2.f;
			items->SetPosition(newPos);
	}
}
