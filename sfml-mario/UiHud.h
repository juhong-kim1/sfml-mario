#pragma once
#include "GameObject.h"
class UiHud : public GameObject
{
protected:
	sf::Text text;
	std::string fontId;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetText();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

};

