#include "stdafx.h"
#include "SceneGameClear.h"
#include "TextGo.h"
#include "SceneDev2.h"

SceneGameClear::SceneGameClear() : Scene(SceneIds::GameClear)
{
}
void SceneGameClear::Init()
{
    fontIds.push_back("fonts/main_font.ttf");

    TextGo* gameClear = new TextGo("fonts/main_font.ttf");
    gameClear->SetString("GAME CLEAR!");
    gameClear->SetCharacterSize(64);
    gameClear->SetFillColor(sf::Color::Green);
    gameClear->SetPosition({ 425.f, 180.f });
    gameClear->SetOrigin(Origins::MC);
    AddGameObject(gameClear);

    scoreText = new TextGo("fonts/main_font.ttf");
    scoreText->SetString("SCORE: 0");
    scoreText->SetCharacterSize(36);
    scoreText->SetFillColor(sf::Color::White);
    scoreText->SetPosition({ 425.f, 250.f });
    scoreText->SetOrigin(Origins::MC);
    AddGameObject(scoreText);

    TextGo* restartText = new TextGo("fonts/main_font.ttf");
    restartText->SetString("Press Enter to restart");
    restartText->SetCharacterSize(24);
    restartText->SetFillColor(sf::Color::Yellow);
    restartText->SetPosition({ 425.f, 320.f });
    restartText->SetOrigin(Origins::MC);
    AddGameObject(restartText);

    Scene::Init();
}

void SceneGameClear::Enter()
{
    sf::Vector2f windowSize = FRAMEWORK.GetWindowSizeF();
    sf::Vector2f center = windowSize * 0.5f;

    worldView.setSize(windowSize);
    worldView.setCenter(center);
    uiView.setSize(windowSize);
    uiView.setCenter(center);

    SOUND_MGR.StopBgm();

    if (scoreText)
    {
        scoreText->SetString("SCORE: " + std::to_string(finalScore));
    }

    Scene::Enter();
}

void SceneGameClear::Update(float dt)
{
    if (InputMgr::GetKeyDown(sf::Keyboard::Enter))
    {
        SCENE_MGR.ChangeScene(SceneIds::Dev2);
    }

    Scene::Update(dt);
}

void SceneGameClear::Draw(sf::RenderWindow& window)
{
    //window.setView(worldView);
    Scene::Draw(window);
}