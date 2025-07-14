#pragma once
#include "Animator.h"
#include "GameObject.h"
#include "HitBox.h"

class GroundTileMap;
class HitBox;

class Enemy : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	GroundTileMap* ground = nullptr;
	HitBox hitBox;

	float positionX = 0.f;
	float positionY = 0.f;

	sf::Vector2f gravity = { 0.f, 1100.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = -80.f;


public:
	Enemy(const std::string& name = "", float x = 0.f, float y = 0.f);
	virtual ~Enemy() = default;

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void isGroundedCheckEnemy();
	void isWallCheckEnemy();
	void isBlockCheckEnemy();
	void SetGroundMapEnemy(GroundTileMap* groundMap) { ground = groundMap; };

	sf::FloatRect GetHitBoxEnemy() const;
};