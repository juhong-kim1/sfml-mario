#pragma once
#include "GameObject.h"
class BreakBlock : public GameObject
{
protected:
	sf::Sprite fragment;
	//std::Vector2f


public:
	BreakBlock(const std::string& name = "");
	virtual ~BreakBlock() = default;

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


};

