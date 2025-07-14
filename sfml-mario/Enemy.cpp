#include "stdafx.h"
#include "Enemy.h"

Enemy::Enemy(const std::string& name, float x, float y)
	:GameObject(name), positionX(x), positionY(y)
{
}

void Enemy::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	body.setPosition(pos);
}

void Enemy::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	body.setRotation(rot);
}

void Enemy::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	body.setScale(s);
}

void Enemy::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	body.setOrigin(o);
}

void Enemy::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		Utils::SetOrigin(body, preset);
	}
}

void Enemy::Init()
{
	animator.SetTarget(&body);

	body.setScale({ 1.f, 1.f });
	SetPosition({ positionX, positionY });
}

void Enemy::Release()
{
}

void Enemy::Reset()
{
	sortingLayer = SortingLayers::Foreground;
	sortingOrder = 0;

	SetOrigin(Origins::BC);

	animator.Play("animations/goomba_move.csv");
}

void Enemy::Update(float dt)
{
	animator.Update(dt);

	velocity.x = -speed;
	position.x += velocity.x * dt;

	SetPosition(position);
}

void Enemy::Draw(sf::RenderWindow& window)
{
	window.draw(body);
}
