#include "stdafx.h"
#include "Flag.h"

Flag::Flag(const std::string& name)
	: GameObject(name)
{
}

void Flag::SetTexture(const std::string& texId)
{
	texture = texId;
}

void Flag::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	sprite.setPosition(pos);
}

void Flag::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	sprite.setRotation(rot);
}

void Flag::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	sprite.setScale(s);
}

void Flag::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	sprite.setOrigin(o);
}

void Flag::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(sprite, preset);
	}
}

void Flag::Init()
{

}

void Flag::Release()
{
}

void Flag::Reset()
{
	sprite.setTexture(TEXTURE_MGR.Get(texture));
	Utils::SetOrigin(sprite, Origins::BC);
}

void Flag::Update(float dt)
{
	hitBox.UpdateTransform(sprite, sprite.getLocalBounds());
}

void Flag::Draw(sf::RenderWindow& window)
{
	window.draw(sprite);
	hitBox.Draw(window);
}

int Flag::GetScoreByHeight(float playerY) const
{
    float flagTop = position.y - 200.f;
    float flagBottom = position.y;

    float relativeHeight = (flagBottom - playerY) / (flagBottom - flagTop);

    relativeHeight = std::max(0.0f, std::min(1.0f, relativeHeight));

    if (relativeHeight >= 0.9f)
    {
        return 1000;
    }
    else if (relativeHeight >= 0.7f)
    {
        return 800;
    }
    else if (relativeHeight >= 0.5f)
    {
        return 500;
    }
    else if (relativeHeight >= 0.3f)
    {
        return 300;
    }
    else
    {
        return 100;
    }
}

