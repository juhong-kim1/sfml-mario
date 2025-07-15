#pragma once
#include "Animator.h"
#include "GameObject.h"
#include "GroundTileMap.h"

class GroundTileMan;

class Item : public GameObject
{
protected:
	sf::Sprite item;
	Animator animator;
	ItemType itemType;

	GroundTileMap* ground = nullptr;

	sf::Vector2f gravity = { 0.f, 1100.f };
	sf::Vector2f velocity = { 0.f, 0.f };
	bool isGrounded = true;
	float speed = 80.f;
	bool activeMushroom = false;

public:
	Item(const std::string& name = "");
	Item(const std::string& name = "", ItemType item = ItemType::Empty);
	virtual ~Item() = default;

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

	void startItemUp();

	ItemType GetItemType() const
	{
		return itemType;
	}

	void isGroundedCheckMushroom();
	void isWallCheckMushroom();
	void isBlockCheckMushroom();
	void SetGroundMapMushroom(GroundTileMap* groundMap) { ground = groundMap; };

	sf::FloatRect GetHitBoxMushroom() const;

	void ActiveMushroom() {	activeMushroom = true; }
};

