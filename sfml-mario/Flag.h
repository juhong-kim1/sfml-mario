#pragma once
#include "GameObject.h"
#include "HitBox.h"

class HitBox;

class Flag : public GameObject
{
protected:
	sf::Sprite sprite;
	sf::Vector2f positionFlag;
	std::string texture;
	HitBox hitBox;

public:
	Flag(const std::string& name = "");
	virtual ~Flag() = default;

	void SetTexture(const std::string& texId);
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

	int GetScoreByHeight(float playerY) const;

	sf::FloatRect GetGlobalBounds() const
	{
		return sprite.getGlobalBounds();
	}

};

