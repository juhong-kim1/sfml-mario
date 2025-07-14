#pragma once
#include "GameObject.h"
class Block : public GameObject
{
protected:
	sf::Sprite block;
	sf::Transform transform;
	sf::IntRect blockRect;
	BlockType blocktype = BlockType::GeneralBlock;



public:
	Block(const std::string& name, BlockType type);
	virtual ~Block() = default;

	void UpdateTransform();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	sf::FloatRect GetGlobalBounds() const
	{
		return block.getGlobalBounds();
	}

	// GameObject을(를) 통해 상속됨
	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void BlockShakeAnimation(float dt);
	void BlockShakeAnimationStart();

};

