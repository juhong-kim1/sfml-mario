#include "stdafx.h"
#include "SceneGameOver.h"
#include "TextGo.h"

SceneGameOver::SceneGameOver() : Scene(SceneIds::GameOver)
{
}

void SceneGameOver::Init()
{
    fontIds.push_back("fonts/main_font.ttf");

    TextGo* gameOver = new TextGo("fonts/main_font.ttf");
    gameOver->SetString("Game Over");
    gameOver->SetCharacterSize(72);
    gameOver->SetFillColor(sf::Color::White);
    gameOver->SetPosition({ 425.f, 220.f });
    gameOver->SetOrigin(Origins::MC);
    AddGameObject(gameOver);

    Scene::Init();
}

void SceneGameOver::Enter()
{
    sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center = windowSize * 0.5f;

    worldView.setSize(windowSize);
    worldView.setCenter(center);
    uiView.setSize(windowSize);
    uiView.setCenter(center);

    SOUND_MGR.StopBgm();

    timer = 0.0f;

    Scene::Enter();
}

void SceneGameOver::Update(float dt)
{
    timer += dt;

    if (timer >= maxTimer)
    {
        SCENE_MGR.ChangeScene(SceneIds::Dev2);
    }

    Scene::Update(dt);
}

void SceneGameOver::Draw(sf::RenderWindow& window)
{
    //window.setView(worldView);
    Scene::Draw(window);
}