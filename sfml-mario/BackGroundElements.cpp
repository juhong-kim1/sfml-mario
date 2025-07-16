#include "stdafx.h"
#include "BackGroundElements.h"

BackGroundElements::BackGroundElements(const std::string& name)
	:GameObject(name)
{
}

void BackGroundElements::SetTexture(const std::string& texId)
{
	texture = texId;
}

void BackGroundElements::Init()
{
}

void BackGroundElements::Release()
{
}

void BackGroundElements::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(texture));
	Utils::SetOrigin(sprite, Origins::BC);
}

void BackGroundElements::Update(float dt)
{
}

void BackGroundElements::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
}

void BackGroundElements::SetPosition(const sf::Vector2f& pos)
{
	position = pos;
	sprite.setPosition(position);
}

void BackGroundElements::SetRotation(float angle)
{
	rotation = angle;
	sprite.setRotation(rotation);
}

void BackGroundElements::SetScale(const sf::Vector2f& s)
{
	scale = s;
	sprite.setScale(scale);
}

void BackGroundElements::SetOrigin(Origins preset)
{
	originPreset = preset;
	if (originPreset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, originPreset);
	}
}

void BackGroundElements::SetOrigin(const sf::Vector2f& newOrigin)
{
	originPreset = Origins::Custom;
	origin = Utils::SetOrigin(sprite, originPreset);
}
