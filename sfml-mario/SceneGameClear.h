#pragma once
#include "Scene.h"

class TextGo;

class SceneGameClear : public Scene
{
protected:
	TextGo* scoreText = nullptr;
	int finalScore = 0;

public:
	SceneGameClear();
	~SceneGameClear() override = default;

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void SetFinalScore(int score) { finalScore = score; }


};

