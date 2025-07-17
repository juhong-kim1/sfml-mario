#pragma once
#include "Scene.h"
#include "GroundTileMap.h"

class AniPlayer;
class Enemy;
class Block;
class Item;
class BreakBlock;
class UiHud;

class SceneDev2 : public Scene
{
protected:
	AniPlayer* player;
	Enemy* enemy;
	UiHud* uiHud;
	std::vector<Block*> blocks;
	std::vector<Enemy*> enemies;
	std::vector<Item*> items;
	std::vector<BreakBlock*> breakBlocks;
	GroundTileMap* groundMap = nullptr;

public:
	SceneDev2();

	void Init() override;
	void Enter() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;
	void AddQuestionBlock(std::string name, float x, float y, ItemType blockitem);
	void AddGeneralBlock(std::string name, float x, float y);
	void AddBush(std::string name, float x, float y, std::string texId);
	void AddCloud(std::string name, float x, float y, std::string texId);
	void AddHill(std::string name, float x, float y, std::string texId);
	void AddEnemy(std::string name, float x, float y);
	std::vector<Block*> GetBlocks() const { return blocks; }
	std::vector<Item*>& GetItems() { return items; }
	std::vector<Enemy*> GetEnemies() { return enemies; }
	std::vector<BreakBlock*> GetBreakBlocks() { return breakBlocks; }
};

