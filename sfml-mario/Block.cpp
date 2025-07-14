#include "stdafx.h"
#include "Block.h"

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





}

void Block::Draw(sf::RenderWindow& window)
{
	window.draw(block);
}

void Block::BlockShakeAnimation(float dt)
{

}

void Block::BlockShakeAnimationStart()
{
}
