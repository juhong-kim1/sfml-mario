#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "GroundTileMap.h"
#include "Block.h"
#include "BackgroundElements.h"
#include "Enemy.h"
#include "Item.h"
#include "Flag.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/background2.png");
	texIds.push_back("graphics/temporary_background2x.png");
	texIds.push_back("graphics/Bush1.png");
	texIds.push_back("graphics/Bush2.png");
	texIds.push_back("graphics/Bush3.png");
	texIds.push_back("graphics/Cloud1.png");
	texIds.push_back("graphics/Cloud2.png");
	texIds.push_back("graphics/Cloud3.png");
	texIds.push_back("graphics/Hill1.png");
	texIds.push_back("graphics/Hill2.png");
	texIds.push_back("graphics/characters2x.png");
	texIds.push_back("graphics/tiles2x.png");
	texIds.push_back("graphics/items2x.png");
	texIds.push_back("graphics/Castle.png");
	texIds.push_back("graphics/FlagPole.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");

	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/stop.csv");
	ANI_CLIP_MGR.Load("animations/mario_die.csv");

	ANI_CLIP_MGR.Load("animations/big_idle.csv");
	ANI_CLIP_MGR.Load("animations/big_run.csv");
	ANI_CLIP_MGR.Load("animations/big_jump.csv");
	ANI_CLIP_MGR.Load("animations/big_sitdown.csv");
	ANI_CLIP_MGR.Load("animations/big_stop.csv");

	ANI_CLIP_MGR.Load("animations/goomba_move.csv");
	ANI_CLIP_MGR.Load("animations/goomba_die.csv");

	ANI_CLIP_MGR.Load("animations/mushroom.csv");
	ANI_CLIP_MGR.Load("animations/coin.csv");

	ANI_CLIP_MGR.Load("animations/get_mushroom.csv");

	/*SpriteGo* background = new SpriteGo("graphics/temporary_background2x.png");
	background->sortingLayer = SortingLayers::Background;
	AddGameObject(background);*/

	SpriteGo* background = new SpriteGo("graphics/background2.png");
	background->sortingLayer = SortingLayers::Background;
	AddGameObject(background);

	SpriteGo* castle = new SpriteGo("graphics/Castle.png");
	castle->SetPosition({ 6528.f, 416.f });
	castle->SetOrigin(Origins::BC);
	AddGameObject(castle);

	float hill1Y = 422.f;
	float hill2Y = 442.f;
	float bushY = 432.f;

	AddHill("", 0.f, hill2Y, "graphics/Hill2.png");  // 나중에 이름 제거
	AddBush("", 368.f, bushY, "graphics/Bush3.png");
	AddHill("", 512.f, hill1Y, "graphics/Hill1.png");
	AddBush("", 752.f, bushY, "graphics/Bush1.png");
	AddBush("", 1328.f, bushY, "graphics/Bush2.png");
	AddHill("", 1536.f, hill2Y, "graphics/Hill2.png");
	AddBush("", 1904.f, bushY, "graphics/Bush3.png");
	AddHill("", 2048.f, hill1Y, "graphics/Hill1.png");
	AddBush("", 2288.f, bushY, "graphics/Bush1.png");
	AddBush("", 2864.f, bushY, "graphics/Bush2.png");
	AddHill("", 3072.f, hill2Y, "graphics/Hill2.png");
	AddBush("", 3440.f, bushY, "graphics/Bush3.png");
	AddHill("", 3584.f, hill1Y, "graphics/Hill1.png");
	AddBush("", 3824.f, bushY, "graphics/Bush1.png");
	AddBush("", 4400.f, bushY, "graphics/Bush2.png");
	AddHill("", 4608.f, hill2Y, "graphics/Hill2.png");
	AddBush("", 5040.f, bushY, "graphics/Bush1.png");
	AddHill("", 5120.f, hill1Y, "graphics/Hill1.png");
	AddBush("", 5360.f, bushY, "graphics/Bush1.png");
	AddHill("", 6144.f, hill2Y, "graphics/Hill2.png");

	AddCloud("", 604.f, 128.f, "graphics/Cloud1.png");
	AddCloud("", 880.f, 144.f, "graphics/Cloud3.png");
	AddCloud("", 1200.f,102.f, "graphics/Cloud2.png");
	AddCloud("", 1800.f, 140.f, "graphics/Cloud1.png");
	AddCloud("", 2148.f, 102.f, "graphics/Cloud1.png");
	AddCloud("", 2400.f, 148.f, "graphics/Cloud3.png");
	AddCloud("", 2700.f, 114.f, "graphics/Cloud2.png");
	AddCloud("", 3340.f, 132.f, "graphics/Cloud1.png");
	AddCloud("", 3732.f, 116.f, "graphics/Cloud1.png");
	AddCloud("", 3974.f, 128.f, "graphics/Cloud3.png");
	AddCloud("", 4300.f, 114.f, "graphics/Cloud2.png");
	AddCloud("", 4900.f, 128.f, "graphics/Cloud1.png");
	AddCloud("", 5200.f, 102.f, "graphics/Cloud1.png");
	AddCloud("", 5550.f, 116.f, "graphics/Cloud3.png");
	AddCloud("", 5900.f, 128.f, "graphics/Cloud1.png");
	AddCloud("", 6260.f, 144.f, "graphics/Cloud1.png");

	groundMap = new GroundTileMap("GroundTileMap");
	AddGameObject(groundMap);

	Flag* flag = new Flag("graphics/FlagPole.png");
	flag->SetTexture("graphics/FlagPole.png");
	flag->sortingLayer = SortingLayers::Background;
	flag->sortingOrder = 0;
	flag->SetPosition({ 6352.f, 384.f });
	flag->SetOrigin(Origins::BC);
	AddGameObject(flag);

	AddQuestionBlock("coin1", 512.f, 288.f, ItemType::Coin);
	AddQuestionBlock("mushroom", 672.f, 288.f, ItemType::Mushroom);
	AddQuestionBlock("coin1", 704.f, 160.f, ItemType::Coin);
	AddQuestionBlock("coin1", 736.f, 288.f, ItemType::Coin);
	AddQuestionBlock("mushroom", 2496.f, 288.f, ItemType::Mushroom);
	AddQuestionBlock("coin1", 3008.f, 160.f, ItemType::Coin);
	AddQuestionBlock("coin1", 3392.f, 288.f, ItemType::Coin);
	AddQuestionBlock("coin1", 3488.f, 288.f, ItemType::Coin);
	AddQuestionBlock("mushroom", 3488.f, 160.f, ItemType::Mushroom);
	AddQuestionBlock("coin1", 3584.f, 288.f, ItemType::Coin);
	AddQuestionBlock("coin1", 4128.f, 160.f, ItemType::Coin);
	AddQuestionBlock("coin1", 4160.f, 160.f, ItemType::Coin);
	AddQuestionBlock("coin1", 5440.f, 288.f, ItemType::Coin);
	
	AddGeneralBlock("General", 640.f, 288.f);
	AddGeneralBlock("General", 704.f, 288.f);
	AddGeneralBlock("General", 768.f, 288.f);
	AddGeneralBlock("General", 2464.f, 288.f);
	AddGeneralBlock("General", 2528.f, 288.f);
	AddGeneralBlock("General", 2624.f, 160.f);
	AddGeneralBlock("General", 2656.f, 160.f);

	for (int i = 1; i < 9; ++i)
	{
		float x = (float)i * 32.f;
		AddGeneralBlock("General", 2528.f + x, 160.f);
	}

	AddGeneralBlock("General", 2912.f, 160.f);
	AddGeneralBlock("General", 2944.f, 160.f);
	AddGeneralBlock("General", 2976.f, 160.f);
	AddGeneralBlock("General", 3008.f, 288.f);
	AddGeneralBlock("General", 3200.f, 288.f);
	AddGeneralBlock("General", 3232.f, 288.f);

	AddGeneralBlock("General", 3776.f, 288.f);
	AddGeneralBlock("General", 3872.f, 160.f);
	AddGeneralBlock("General", 3904.f, 160.f);
	AddGeneralBlock("General", 3936.f, 160.f);

	AddGeneralBlock("General", 4096.f, 160.f);
	AddGeneralBlock("General", 4128.f, 288.f);
	AddGeneralBlock("General", 4160.f, 288.f);
	AddGeneralBlock("General", 4192.f, 160.f);

	AddGeneralBlock("General", 5376.f, 288.f);
	AddGeneralBlock("General", 5408.f, 288.f);
	AddGeneralBlock("General", 5472.f, 288.f);

	player = new AniPlayer();
	player->SetGroundMap(groundMap);
	AddGameObject(player);

	AddEnemy("", 700.f, 380.f);
	AddEnemy("", 1300.f, 380.f);
	AddEnemy("", 1600.f, 380.f);
	AddEnemy("", 1664.f, 380.f);
	AddEnemy("", 2600.f, 110.f);
	AddEnemy("", 2670.f, 110.f);
	AddEnemy("", 3100.f, 380.f);
	AddEnemy("", 3164.f, 380.f);
	AddEnemy("", 3664.f, 380.f);
	AddEnemy("", 3728.f, 380.f);
	AddEnemy("", 3900.f, 380.f);
	AddEnemy("", 3954.f, 380.f);
	AddEnemy("", 4028.f, 380.f);
	AddEnemy("", 4092.f, 380.f);
	AddEnemy("", 5560.f, 380.f);
	AddEnemy("", 5624.f, 380.f);

	Scene::Init();
}

void SceneDev2::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center { size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, 120.f });


	Scene::Enter();
}

void SceneDev2::Update(float dt)
{
	//Scene::Update(dt);



	if (player != nullptr && player->GetPosition().x > worldView.getCenter().x)
	{
		worldView.setCenter(player->GetPosition().x , 240.f);
	}

	for (auto* enemy : enemies)
	{
		if (!enemy->GetActive() && !enemy->IsDying())
		{
			float distance = abs(player->GetPosition().x - enemy->GetPosition().x);
			if (distance <= 600.f)
			{
				std::cout << "굼바 출현" << std::endl;
				enemy->SetActive(true);
			}
		}
	}

	Scene::Update(dt);
}

void SceneDev2::AddQuestionBlock(std::string name, float x, float y, ItemType blockItem)
{
	Block* block = new Block(name, BlockType::QuestionBlock);
	block->SetPosition({ x , y });
	AddGameObject(block);
	blocks.push_back(block);

	Item* item = new Item(name, blockItem);
	item->SetPosition({ x ,y });
	item->SetActive(false);
	item->SetGroundMapMushroom(groundMap);
	AddGameObject(item);
	items.push_back(item);

	block->SetItem(item);
}

void SceneDev2::AddGeneralBlock(std::string name, float x, float y)
{
	Block* block = new Block(name, BlockType::GeneralBlock);
	block->SetPosition({ x, y });
	AddGameObject(block);
	blocks.push_back(block);
}

void SceneDev2::AddBush(std::string name, float x, float y, std::string texId)
{
	BackGroundElements* bush = new BackGroundElements(name);
	bush->SetTexture(texId);
	bush->SetPosition({ x, y });
	bush->sortingLayer = SortingLayers::Background;
	AddGameObject(bush);
}

void SceneDev2::AddCloud(std::string name, float x, float y, std::string texId)
{
	BackGroundElements* cloud = new BackGroundElements(name);
	cloud->SetTexture(texId);
	cloud->SetPosition({ x, y });
	cloud->sortingLayer = SortingLayers::Background;
	AddGameObject(cloud);
}

void SceneDev2::AddHill(std::string name, float x, float y, std::string texId)
{
	BackGroundElements* hill = new BackGroundElements(name);
	hill->SetTexture(texId);
	hill->SetPosition({ x, y });
	hill->sortingLayer = SortingLayers::Background;
	AddGameObject(hill);
}

void SceneDev2::AddEnemy(std::string name, float x, float y)
{
	Enemy* enemy = new Enemy("Enemy", x, y);
	enemy->SetGroundMapEnemy(groundMap);
	enemy->SetActive(false);
	AddGameObject(enemy);
	enemies.push_back(enemy);
}