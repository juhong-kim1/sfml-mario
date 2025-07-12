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
			int texIndex = 0;

			if (i >= count.y - 2)
			{
				texIndex = 1;
			}


            int quadIndex = i * count.x + j;

            tileTypes[quadIndex] = texIndex;
            sf::Vector2f quadPos(j * size.x, i * size.y);

            for (int k = 0; k < 4; ++k)
			{
                int vertexIndex = quadIndex * 4 + k;

                va[vertexIndex].position = quadPos + posOffset[k];
                va[vertexIndex].texCoords = texCoords[k];
                va[vertexIndex].color = (texIndex == 0) ? sf::Color::Transparent : sf::Color::White;
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
	return tileTypes[index] == 3;
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
	return tileTypes[index] == 1;
}

float GroundTileMap::GetGroundHeight()
{
	return (cellCount.y - 1) * cellSize.y + position.y;
}



void GroundTileMap::Init()
{
	sortingLayer = SortingLayers::Background;
	sortingOrder = 0;
}

void GroundTileMap::SetMapSize(int width, int height, float cellWidth, float cellHeight)
{
	Set({ width, height }, { cellWidth, cellHeight });
}

void GroundTileMap::SetMapSize(int width, int height)
{
	SetMapSize(width, height, 32.f, 32.f);
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
