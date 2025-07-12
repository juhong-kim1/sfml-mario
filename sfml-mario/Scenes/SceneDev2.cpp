#include "stdafx.h"
#include "SceneDev2.h"
#include "TextGo.h"
#include "AniPlayer.h"
#include "SpriteGo.h"
#include "GroundTileMap.h"

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