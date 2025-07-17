#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetScore(int newScore)
{
	score = newScore;
	UpdateScore();
}

void UiHud::AddScore(int points)
{
	score += points;
	UpdateScore();
}

void UiHud::SetCoins(int newCoins)
{
	coins = newCoins;
	UpdateCoins();
}

void UiHud::AddCoin()
{
	coins++;
	UpdateCoins();
}

void UiHud::SetWorldName(const std::string& name)
{
	worldName = name;
	UpdateWorld();
}

void UiHud::SetTime(int time)
{
	gameTime = time;
	UpdateTime();
}

void UiHud::SetLives(int newLives)
{
	lives = newLives;
	UpdateLives();
}

void UiHud::LoseLife()
{
	lives--;
	if (lives <= 0)
	{
		isGameOver = true;
	}
	UpdateLives();
}

void UiHud::UpdateScore()
{
	textScore.setString(std::to_string(score));
	Utils::SetOrigin(textScore, Origins::TC);
}

void UiHud::UpdateCoins()
{
	textCoins.setString(std::to_string(coins));
	Utils::SetOrigin(textCoins, Origins::TC);
}

void UiHud::UpdateWorld()
{
	textWorld.setString(worldName);
	Utils::SetOrigin(textWorld, Origins::TC);
}

void UiHud::UpdateTime()
{
	textTime.setString(std::to_string(gameTime));
	Utils::SetOrigin(textTime, Origins::TC);
}

void UiHud::UpdateLives()
{
	textLives.setString(std::to_string(lives));
	Utils::SetOrigin(textLives, Origins::TC);
}

void UiHud::SetText()
{
	std::string textTop = "Score     Coins     World     Time     Lives";
	text.setScale({1.f,1.f});
	text.setString(textTop);
	Utils::SetOrigin(text, Origins::TL);
}

void UiHud::Init()
{
	fontId = "fonts/main_font.ttf";

	sortingLayer = SortingLayers::UI;
	sortingOrder = 0;

	sf::FloatRect bounds = FRAMEWORK.GetWindowBounds();

	text.setCharacterSize(22);
	text.setFillColor(sf::Color::White);
	text.setPosition(20, 0);

	textScore.setCharacterSize(22);
	textScore.setFillColor(sf::Color::White);
	textScore.setPosition(65, 25);

	textCoins.setCharacterSize(22);
	textCoins.setFillColor(sf::Color::White);
	textCoins.setPosition(244, 25);

	textWorld.setCharacterSize(22);
	textWorld.setFillColor(sf::Color::White);
	textWorld.setPosition(424, 25);

	textTime.setCharacterSize(22);
	textTime.setFillColor(sf::Color::White);
	textTime.setPosition(595, 25);

	textLives.setCharacterSize(22);
	textLives.setFillColor(sf::Color::White);
	textLives.setPosition(764, 25);


}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	textScore.setFont(FONT_MGR.Get(fontId));
	textCoins.setFont(FONT_MGR.Get(fontId));
	textWorld.setFont(FONT_MGR.Get(fontId));
	textTime.setFont(FONT_MGR.Get(fontId));
	textLives.setFont(FONT_MGR.Get(fontId));

	score = 0;
	coins = 0;
	worldName = "1-1";
	gameTime = 400;
	isTimeFreezed = false;

	if (isGameOver)
	{
		lives = 3;
		isGameOver = false;
	}

	timeTimer = 0.0f;

	SetText();
	UpdateScore();
	UpdateCoins();
	UpdateWorld();
	UpdateTime();
	UpdateLives();
}

void UiHud::Update(float dt)
{
	if (isGameOver || isTimeFreezed)
	{
		return;
	}

	timeTimer += dt;
	if (timeTimer >= 1.0f)
	{
		timeTimer = 0.0f;
		if (gameTime > 0)
		{
			gameTime--;
			UpdateTime();
		}

		if (gameTime <= 0)
		{
			LoseLife();

			if (!isGameOver)
			{
				gameTime = 400;
				UpdateTime();
			}
		}
	}
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(text);
	window.draw(textScore);
	window.draw(textCoins);
	window.draw(textWorld);
	window.draw(textTime);
	window.draw(textLives);
}

void UiHud::ApplyTimeBonus()
{
	if (gameTime > 0)
	{
		int bonus = gameTime * 50;

		AddScore(bonus);
		FreezeTime();

		isGameOver = true;

		/*gameTime = 0;
		UpdateTime();*/
	}
}
	