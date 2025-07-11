#pragma once
#include "Scene.h"

class AniPlayer;

class SceneDev2 : public Scene
{
protected:
	AniPlayer* player;



public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;

};

