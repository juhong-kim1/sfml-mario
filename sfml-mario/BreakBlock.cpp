#include "stdafx.h"
#include "BreakBlock.h"

BreakBlock::BreakBlock(const std::string& name)
	: GameObject(name)
{
}

void BreakBlock::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	fragment.setPosition(pos);
}

void BreakBlock::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	fragment.setRotation(rot);
}

void BreakBlock::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	fragment.setScale(s);
}

void BreakBlock::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	fragment.setOrigin(o);
}

void BreakBlock::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(fragment, preset);
	}
}

void BreakBlock::Init()
{
}

void BreakBlock::Release()
{
}

void BreakBlock::Reset()
{
}

void BreakBlock::Update(float dt)
{
}

void BreakBlock::Draw(sf::RenderWindow& window)
{
	window.draw(fragment);
}

