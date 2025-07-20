#include "stdafx.h"
#include "SceneDev1.h"
#include "TextGo.h"
#include "Framework.h"
#include "ResourceMgr.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "UiHud.h"

SceneDev1::SceneDev1(): Scene(SceneIds::Dev1)
{
}

void SceneDev1::Init()
{
	fontIds.push_back("fonts/main_font.ttf");

	uiHud = (UiHud*)AddGameObject(new UiHud());

	Scene::Init();
}

void SceneDev1::Enter()
{
	auto size = FRAMEWORK.GetWindowSizeF();
	sf::Vector2f center{ size.x * 0.5f, size.y * 0.5f };
	uiView.setSize(size);
	uiView.setCenter(center);
	worldView.setSize(size);
	worldView.setCenter({ 0.f, 120.f });

	Scene::Enter();
}

void SceneDev1::Update(float dt)
{
	
}

void SceneDev1::Draw(sf::RenderWindow& window)
{
	window.setView(worldView);
	Scene::Draw(window);

	window.setView(uiView);
	uiHud->Draw(window);
}
