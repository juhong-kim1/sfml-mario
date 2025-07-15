#include "stdafx.h"
#include "Item.h"

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

}

void Item::Update(float dt)
{
	animator.Update(dt);

}

void Item::Draw(sf::RenderWindow& window)
{
	window.draw(item);
}

void Item::startItemUp()
{
}
