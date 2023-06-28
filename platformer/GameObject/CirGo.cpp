#include "stdafx.h"
#include "CirGo.h"

CirGo::CirGo(const std::string n)
	:GameObject(n)
{
}

CirGo::~CirGo()
{
}

void CirGo::SetPosition(float x, float y)
{
	position.x = x;
	position.y = y;
	circle.setPosition(position);
}

void CirGo::SetPosition(const sf::Vector2f& p)
{
	position = p;
	circle.setPosition(p);
}

void CirGo::SetOrigin(Origins origin)
{
	Utils::SetOrigin(circle, origin);
}

void CirGo::SetOrigin(float x, float y)
{
	circle.setOrigin(x, y);
}

void CirGo::Init()
{

}

void CirGo::Reset()
{

}

void CirGo::Release()
{

}

void CirGo::Update(float dt)
{

}

void CirGo::Draw(sf::RenderWindow& window)
{
	window.draw(circle);
}
