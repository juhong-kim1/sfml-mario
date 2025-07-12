#pragma once
#include "Scene.h"

class AniPlayer;
class Block;

class SceneDev2 : public Scene
{
protected:
	AniPlayer* player;



public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void AddQuestionBlock(std::string name, float x, float y);
	void AddGeneralBlock(std::string name, float x, float y);
};

