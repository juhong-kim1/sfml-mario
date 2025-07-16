#pragma once
#include "Animator.h"
#include "HitBox.h"

class HitBox;
class GroundTileMap;
class Flag;

class AniPlayer : public GameObject
{
protected:
	sf::Sprite body;
	Animator animator;
	GroundTileMap* ground = nullptr;
	Mario mario;
	Flag* flag;

	sf::Vector2f gravity = { 0.f, 1100.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	sf::Vector2f velocityJump = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = 220.f;
	//float speed = 1000.f;

	
	float maxJumpTime = 0.5f;
	float currentJumpTime = 0.f;

	bool isMarioDie = false;
	bool deathProcessed = false;
	float dieCurrentTime = 0.0f;
	sf::Vector2f originPosition;

	bool isInvincible = false;
	float invincibleTime = 0.0f;
	float maxInvincibleTime = 2.0f;

	HitBox hitBox;


public:
	AniPlayer(const std::string& name = "");
	~AniPlayer() = default;

	//bool CheckBorder(const sf::Vector2f pos);

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float angle) override;
	void SetScale(const sf::Vector2f& scale) override;

	void SetOrigin(Origins preset) override;
	void SetOrigin(const sf::Vector2f& newOrigin) override;

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	sf::FloatRect GetHitBoxBottom() const;
	sf::FloatRect GetHitBoxTop() const;
	sf::FloatRect GetHitBoxLeft() const;
	sf::FloatRect GetHitBoxRight() const;

	void isGroundedCheck();
	void isWallCheck();
	void isBlockCheck();
	void isEnemyCheck();
	//void isFlagCheck();
	void SetGroundMap(GroundTileMap* groundMap) { ground = groundMap; };

	void MarioDie();
};
