#pragma once
#include "GameObject.h"

class GroundTileMap : public GameObject
{
protected:
	sf::VertexArray va;
	std::string spriteSheetId = "graphics/tiles2x.png";
	sf::Texture* texture = nullptr;
	sf::Transform transform;
	std::vector<int> tileTypes;

	sf::Vector2i cellCount;
	sf::Vector2f cellSize;

public:
	GroundTileMap(const std::string& name = "");
	virtual ~GroundTileMap() = default;

	void Set(const sf::Vector2i& count, const sf::Vector2f& size);
	void CreateHole(int startX, int startY, int width, int height);
	void CreatePipe(int x, int height);
	void CreateStairs(int startX, int maxHeight);
	void CreateReverseStairs(int startX, int maxHeight);
	void UpdateTransform();

	void SetPosition(const sf::Vector2f& pos) override;
	void SetRotation(float rot) override;
	void SetScale(const sf::Vector2f& s) override;
	void SetOrigin(const sf::Vector2f& o) override;
	void SetOrigin(Origins preset) override;

	bool IsWallAt(const sf::Vector2f& worldPos);
	bool IsGroundAt(const sf::Vector2f& worldPos);
	float GetGroundHeight();

	// GameObject을(를) 통해 상속됨
	void Init() override;

	void SetMapSize(int width, int height, float cellWidth, float cellHeight);

	void SetMapSize(int width, int height);

	void Release() override;

	void Reset() override;

	void Update(float dt) override;

	void Draw(sf::RenderWindow& window) override;

};

