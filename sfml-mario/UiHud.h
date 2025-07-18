#pragma once
#include "GameObject.h"
class UiHud : public GameObject
{
protected:
	sf::Text text;
	sf::Text textScore;
	sf::Text textCoins;
	sf::Text textWorld;
	sf::Text textTime;
	sf::Text textLives;

	std::string fontId;

	int score = 0;
	int coins = 0;
	std::string worldName = "1-1";
	int gameTime = 400;
	int lives = 3;
	float timeTimer = 0.0f;
	bool isGameOver = false;
	bool isTimeFreezed = false;

public:
	UiHud(const std::string& name = "");
	virtual ~UiHud() = default;

	void SetScore(int newScore);
	void AddScore(int points);
	void SetCoins(int newCoins);
	void AddCoin();
	void SetWorldName(const std::string& name);
	void SetTime(int time);
	void SetLives(int newLives);
	void LoseLife();

	void UpdateScore();
	void UpdateCoins();
	void UpdateWorld();
	void UpdateTime();
	void UpdateLives();

	void SetText();

	void Init() override;
	void Release() override;
	void Reset() override;
	void Update(float dt) override;
	void Draw(sf::RenderWindow& window) override;

	void ApplyTimeBonus();
	//void FreezeTime() { isTimeFreezed = true; }
	int GetTime() const { return gameTime; }
};

