#include "stdafx.h"
#include "GroundTileMap.h"

TileMap::TileMap(const std::string& name)
	:GameObject(name)
{
}

void TileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{


}

void TileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	//UpdateTransform();
}

void TileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	//UpdateTransform();
}

void TileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	//UpdateTransform();
}

void TileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	//UpdateTransform();
}

void TileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	//if (preset != Origins::Custom)
	//{
	//	sf::FloatRect rect;
	//	rect.width = cellCount.x * cellSize.x;
	//	rect.height = cellCount.y * cellSize.y;

	//	origin.x = rect.width * ((int)preset % 3) * 0.5f;
	//	origin.y = rect.height * ((int)preset / 3) * 0.5f;
	//}
	//UpdateTransform();
}

void TileMap::Init()
{
}

void TileMap::Release()
{
}

void TileMap::Reset()
{
}

void TileMap::Update(float dt)
{
}

void TileMap::Draw(sf::RenderWindow& window)
{
}
