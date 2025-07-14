#pragma once
#include "Scene.h"
#include "GroundTileMap.h"

class AniPlayer;
class Enemy;
class Block;


class SceneDev2 : public Scene
{
protected:
	AniPlayer* player;
	Enemy* enemy;
	std::vector<Block*> blocks;
	GroundTileMap* groundMap = nullptr;

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void AddQuestionBlock(std::string name, float x, float y);
	void AddGeneralBlock(std::string name, float x, float y);
	void AddBush(std::string name, float x, float y, std::string texId);
	void AddCloud(std::string name, float x, float y, std::string texId);
	void AddHill(std::string name, float x, float y, std::string texId);
	void AddEnemy(std::string name, float x, float y);
	std::vector<Block*> GetBlocks() const { return blocks; }
};

