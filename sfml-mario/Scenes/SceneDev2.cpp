#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "GroundTileMap.h"
#include "Block.h"

SceneDev2::SceneDev2() : Scene(SceneIds::Dev2)
{
}

void SceneDev2::Init()
{
	texIds.push_back("graphics/temporary_background2x.png");
	texIds.push_back("graphics/characters2x.png");
	texIds.push_back("graphics/tiles2x.png");

	fontIds.push_back("fonts/DS-DIGIT.ttf");



	ANI_CLIP_MGR.Load("animations/idle.csv");
	ANI_CLIP_MGR.Load("animations/run.csv");
	ANI_CLIP_MGR.Load("animations/jump.csv");
	ANI_CLIP_MGR.Load("animations/stop.csv");
	ANI_CLIP_MGR.Load("animations/big_idle.csv");
	ANI_CLIP_MGR.Load("animations/big_run.csv");
	ANI_CLIP_MGR.Load("animations/big_jump.csv");

	


	SpriteGo* background = new SpriteGo("graphics/temporary_background2x.png");
	background->sortingLayer = SortingLayers::Background;
	AddGameObject(background);

	AddQuestionBlock("Question", 512.f, 288.f);  // 나중에 이름 제거
	AddQuestionBlock("Question", 672.f, 288.f);
	AddQuestionBlock("Question", 704.f, 160.f);
	AddQuestionBlock("Question", 736.f, 288.f);
	AddQuestionBlock("Question", 2496.f, 288.f);
	AddQuestionBlock("Question", 3008.f, 160.f);
	AddQuestionBlock("Question", 3392.f, 288.f);
	AddQuestionBlock("Question", 3488.f, 288.f);
	AddQuestionBlock("Question", 3488.f, 160.f);
	AddQuestionBlock("Question", 3584.f, 288.f);
	AddQuestionBlock("Question", 4128.f, 160.f);
	AddQuestionBlock("Question", 4160.f, 160.f);
	AddQuestionBlock("Question", 5440.f, 288.f);
	
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

	GroundTileMap* groundMap = new GroundTileMap("GroundTileMap");
	AddGameObject(groundMap);

	player = new AniPlayer();
	AddGameObject(player);

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
	Scene::Update(dt);


	if (player != nullptr && player->GetPosition().x > worldView.getCenter().x)
	{
		worldView.setCenter(player->GetPosition().x , 240.f);
	}

}

void SceneDev2::AddQuestionBlock(std::string name, float x, float y)
{
	Block* block = new Block(name, BlockType::QuestionBlock);
	block->SetPosition({ x, y });
	AddGameObject(block);
}

void SceneDev2::AddGeneralBlock(std::string name, float x, float y)
{
	Block* block = new Block(name, BlockType::GeneralBlock);
	block->SetPosition({ x, y });
	AddGameObject(block);
}
