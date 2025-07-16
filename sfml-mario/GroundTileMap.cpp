#include "stdafx.h"
#include "GroundTileMap.h"

GroundTileMap::GroundTileMap(const std::string& name)
	:GameObject(name)
{
}

void GroundTileMap::Set(const sf::Vector2i& count, const sf::Vector2f& size)
{
    cellCount = count;
    cellSize = size;
    va.clear();
    va.setPrimitiveType(sf::Quads);

    int totalVertices = count.x * count.y * 4;

    va.resize(totalVertices);
    tileTypes.clear();
    tileTypes.resize(count.x * count.y);

    sf::Vector2f posOffset[4] = {
        { 0.f, 0.f },
        { size.x, 0.f },
        { size.x, size.y },
        { 0.f, size.y },
    };

    sf::Vector2f texCoords[4] = {
        { 0.f, 0.f },
        { 32.f, 0.f },
        { 32.f, 32.f },
        { 0.f, 32.f },
    };

    for (int i = 0; i < count.y; ++i)
	{
        for (int j = 0; j < count.x; ++j)
		{
			int texIndex = static_cast<int>(TileType::Empty);

			if (i >= count.y - 2)
			{
				texIndex = static_cast<int>(TileType::Ground);
			}


            int quadIndex = i * count.x + j;

            tileTypes[quadIndex] = texIndex;
            sf::Vector2f quadPos(j * size.x, i * size.y);

            for (int k = 0; k < 4; ++k)
			{
                int vertexIndex = quadIndex * 4 + k;

                va[vertexIndex].position = quadPos + posOffset[k];
                va[vertexIndex].texCoords = texCoords[k];
				va[vertexIndex].color = (texIndex == static_cast<int>(TileType::Empty)) ? sf::Color::Transparent : sf::Color::White;
            }
        }
    }

	CreateHole(69, 13, 2, 2);
	CreateHole(86, 13, 3, 2);
    CreateHole(153, 13, 2, 2);

    CreatePipe(28, 2);
    CreatePipe(38, 3);
    CreatePipe(46, 4);
    CreatePipe(57, 4);
    CreatePipe(163, 2);
    CreatePipe(179, 2);

    CreateStairs(134, 4);
    CreateStairs(148, 4);
    CreateStairs(149, 4);
    CreateStairs(181, 8);
    CreateStairs(182, 8);
    CreateStairs(198, 1);

    CreateReverseStairs(140, 4);
    CreateReverseStairs(155, 4);


}

void GroundTileMap::CreateHole(int startX, int startY, int width, int height)
{
	for (int y = startY; y < startY + height; ++y)
	{
		for (int x = startX; x < startX + width; ++x)
		{
			int quadIndex = y * cellCount.x + x;
			tileTypes[quadIndex] = 0;

			for (int k = 0; k < 4; ++k)
			{
				int vertexIndex = quadIndex * 4 + k;
				va[vertexIndex].color = sf::Color::Transparent;
			}
		}
	}
}

void GroundTileMap::CreatePipe(int x, int height)
{
     int startY = cellCount.y - 2 - height;

    for (int y = startY + 1; y < cellCount.y - 2; ++y)
    {
        if (x >= 0 && x < cellCount.x && y >= 0 && y < cellCount.y)
        {
            int quadIndex = y * cellCount.x + x;
            tileTypes[quadIndex] = static_cast<int>(TileType::PipeBody);

            sf::Vector2f texCoords[4] = {
                {0.f, 288.f},
                {32.f, 288.f},
                {32.f, 320.f},
                {0.f, 320.f}
            };

            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = quadIndex * 4 + k;
                va[vertexIndex].texCoords = texCoords[k];
                va[vertexIndex].color = sf::Color::White;
            }
        }

        if (x + 1 >= 0 && x + 1 < cellCount.x && y >= 0 && y < cellCount.y)
        {
            int quadIndex = y * cellCount.x + (x + 1);
            tileTypes[quadIndex] = static_cast<int>(TileType::PipeBody);


            sf::Vector2f texCoords[4] = {
                {32.f, 288.f},
                {64.f, 288.f},
                {64.f, 320.f},
                {32.f, 320.f}
            };

            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = quadIndex * 4 + k;
                va[vertexIndex].texCoords = texCoords[k];
                va[vertexIndex].color = sf::Color::White;
            }
        }
    }

        if (x >= 0 && x < cellCount.x && startY >= 0 && startY < cellCount.y)
        {
            int quadIndex = startY * cellCount.x + x;
            tileTypes[quadIndex] = static_cast<int>(TileType::PipeHead);

            sf::Vector2f texCoords[4] = {
                {0.f, 256.f},
                {32.f, 256.f},
                {32.f, 288.f},
                {0.f, 288.f}
            };

            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = quadIndex * 4 + k;
                va[vertexIndex].texCoords = texCoords[k];
                va[vertexIndex].color = sf::Color::White;
            }
        }
 

   
        if (x + 1 >= 0 && x + 1 < cellCount.x && startY >= 0 && startY < cellCount.y)
        {
            int quadIndex = startY * cellCount.x + (x + 1);
            tileTypes[quadIndex] = static_cast<int>(TileType::PipeHead);

            sf::Vector2f texCoords[4] = {
                {32.f, 256.f},
                {64.f, 256.f},
                {64.f, 288.f},
                {32.f, 288.f}
            };

            for (int k = 0; k < 4; ++k)
            {
                int vertexIndex = quadIndex * 4 + k;
                va[vertexIndex].texCoords = texCoords[k];
                va[vertexIndex].color = sf::Color::White;
            }
        }
    
}

void GroundTileMap::CreateStairs(int startX, int maxHeight)
{
    for (int i = 0; i < maxHeight; ++i)
    {
        int stepHeight = i + 1;
        int stepY = cellCount.y - 2 - stepHeight;

        for (int y = stepY; y < cellCount.y - 2; ++y)
        {
            int stairX = startX + i;
            if (stairX >= 0 && stairX < cellCount.x && y >= 0 && y < cellCount.y)
            {
                int quadIndex = y * cellCount.x + stairX;
                tileTypes[quadIndex] = static_cast<int>(TileType::Stair);

                sf::Vector2f texCoords[4] = {
                    {0.f, 32.f},
                    {32.f, 32.f},
                    {32.f, 64.f},
                    {0.f, 64.f}
                };

                for (int k = 0; k < 4; ++k)
                {
                    int vertexIndex = quadIndex * 4 + k;
                    va[vertexIndex].texCoords = texCoords[k];
                    va[vertexIndex].color = sf::Color::White;
                }
            }
        }
    }
}

void GroundTileMap::CreateReverseStairs(int startX, int maxHeight)
{
    for (int i = 0; i < maxHeight; ++i)
    {
        int stepHeight = maxHeight - i;
        int stepY = cellCount.y - 2 - stepHeight;

        for (int y = stepY; y < cellCount.y - 2; ++y)
        {
            int stairX = startX + i;
            if (stairX >= 0 && stairX < cellCount.x && y >= 0 && y < cellCount.y)
            {
                int quadIndex = y * cellCount.x + stairX;
                tileTypes[quadIndex] = static_cast<int>(TileType::Stair);

                sf::Vector2f texCoords[4] = {
                    {0.f, 32.f},
                    {32.f, 32.f},
                    {32.f, 64.f},
                    {0.f, 64.f}
                };

                for (int k = 0; k < 4; ++k)
                {
                    int vertexIndex = quadIndex * 4 + k;
                    va[vertexIndex].texCoords = texCoords[k];
                    va[vertexIndex].color = sf::Color::White;
                }
            }
        }
    }
}

void GroundTileMap::UpdateTransform()
{
	transform = sf::Transform::Identity;
	transform.translate(position);
	transform.rotate(rotation);
	transform.scale(scale);
	transform.translate(-origin);
}

void GroundTileMap::SetPosition(const sf::Vector2f& pos)
{
	GameObject::SetPosition(pos);
	UpdateTransform();
}

void GroundTileMap::SetRotation(float rot)
{
	GameObject::SetRotation(rot);
	UpdateTransform();
}

void GroundTileMap::SetScale(const sf::Vector2f& s)
{
	GameObject::SetScale(s);
	UpdateTransform();
}

void GroundTileMap::SetOrigin(const sf::Vector2f& o)
{
	GameObject::SetOrigin(o);
	UpdateTransform();
}

void GroundTileMap::SetOrigin(Origins preset)
{
	GameObject::SetOrigin(preset);
	if (preset != Origins::Custom)
	{
		sf::FloatRect rect;
		rect.width = cellCount.x * cellSize.x;
		rect.height = cellCount.y * cellSize.y;

		origin.x = rect.width * ((int)preset % 3) * 0.5f;
		origin.y = rect.height * ((int)preset / 3) * 0.5f;
	}
	UpdateTransform();
}

bool GroundTileMap::IsWallAt(const sf::Vector2f& worldPos)
{
    sf::Vector2f localPos = transform.getInverse().transformPoint(worldPos);
    int x = static_cast<int>(localPos.x / cellSize.x);
    int y = static_cast<int>(localPos.y / cellSize.y);

    if (x < 0 || y < 0 || x >= cellCount.x || y >= cellCount.y)
    {
        return true;
    }

    int index = y * cellCount.x + x;
    int tileType = tileTypes[index];

    return (tileType == static_cast<int>(TileType::Ground) || tileType == static_cast<int>(TileType::PipeHead) || tileType == static_cast<int>(TileType::PipeBody) || tileType == static_cast<int>(TileType::Stair));
}

bool GroundTileMap::IsGroundAt(const sf::Vector2f& worldPos)
{
	sf::Vector2f localPos = transform.getInverse().transformPoint(worldPos);
	int x = static_cast<int>(localPos.x / cellSize.x);
	int y = static_cast<int>(localPos.y / cellSize.y);

	if (x < 0 || y < 0 || x >= cellCount.x || y >= cellCount.y)
	{
		return false;
	}

	int index = y * cellCount.x + x;
	return (tileTypes[index] == static_cast<int>(TileType::Ground) || tileTypes[index] == static_cast<int>(TileType::PipeHead) || tileTypes[index] == static_cast<int>(TileType::PipeBody) || tileTypes[index] == static_cast<int>(TileType::Stair));
}

void GroundTileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void GroundTileMap::Release()
{
}

void GroundTileMap::Reset()
{
    texture = &TEXTURE_MGR.Get(spriteSheetId);
    Set({ 211, 15 }, { 32.f, 32.f });

	SetOrigin(Origins::TL);
    SetScale({ 1.f, 1.f });
    SetPosition({ 0.f, 0.f });
}


void GroundTileMap::Update(float dt)
{
}

void GroundTileMap::Draw(sf::RenderWindow& window)
{
	sf::RenderStates state;
	state.texture = texture;
	state.transform = transform;
	window.draw(va, state);
}
