#include "stdafx.h"
#include "UiHud.h"

UiHud::UiHud(const std::string& name)
	: GameObject(name)
{
}

void UiHud::SetText()
{
	std::string textTop = "Score Coins World Time Lives";
	text.setScale({1.f,1.f});
	text.setString(textTop);
	Utils::SetOrigin(text, Origins::TL);
}

void UiHud::Init()
{
	fontId = "graphics/main_font.ttf";


	text.setFont(FONT_MGR.Get(fontId));

	// 텍스트 속성 설정
	text.setCharacterSize(100);
	text.setFillColor(sf::Color::White);
	text.setPosition(20, 20);

	SetText();
}

void UiHud::Release()
{
}

void UiHud::Reset()
{
	text.setFont(FONT_MGR.Get(fontId));
	SetText();
}

void UiHud::Update(float dt)
{
}

void UiHud::Draw(sf::RenderWindow& window)
{
	window.draw(text);
}
	