#include "stdafx.h"
#include "FloatRectGo.h"

FloatRectGo::FloatRectGo(const std::string n) : GameObject(n)
{
}

FloatRectGo::~FloatRectGo()
{
}

void FloatRectGo::SetSize(const sf::Vector2f& size)
{
	frect.width = size.x;
	frect.height = size.y;
}

void FloatRectGo::SetSize(float x, float y)
{
	frect.width = x;
	frect.height = y;
}

void FloatRectGo::SetPosition(float x, float y)
{
	frect.left = x - frect.width / 2.f;
	frect.top = y - frect.height / 2.f;
}

void FloatRectGo::SetPosition(const sf::Vector2f& size)
{
	frect.left = size.x - frect.width / 2.f;
	frect.top = size.y - frect.height / 2.f;
}

void FloatRectGo::Init()
{

}

void FloatRectGo::Reset()
{

}

void FloatRectGo::Release()
{

}

void FloatRectGo::Update(float dt)
{

}

void FloatRectGo::Draw(sf::RenderWindow& window)
{
	
}
