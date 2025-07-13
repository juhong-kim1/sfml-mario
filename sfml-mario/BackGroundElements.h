#pragma once
#include "GameObject.h"
class BackGroundElements : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Vector2f positionElements;
	std::string texture;

public:
	BackGroundElements(const std::string& name);
	virtual ~BackGroundElements() = default;

	void SetTexture(const std::string& texId);

	// GameObject을(를) 통해 상속됨
	void Init() override;

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

	void SetPosition(const sf::Vector2f& pos);
	void SetRotation(float angle);
	void SetScale(const sf::Vector2f& s);
	void SetOrigin(Origins preset);
	void SetOrigin(const sf::Vector2f& newOrigin);
};

