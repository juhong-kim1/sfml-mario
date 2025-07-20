#pragma once
#include "Scene.h"

class SceneGameOver : public Scene
{
protected:
	float timer = 0.0f;
	float maxTimer = 3.0f;

public:
	SceneGameOver();
	~SceneGameOver() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
};

