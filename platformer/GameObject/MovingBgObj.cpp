#include "MovingBgObj.h"
#include "Utils.h"
#include "stdafx.h"
MovingBgObj::MovingBgObj(
	const std::string n)
	: SpriteGo(n), accumTime (0.f), widthY(0.f), heightY(0.f)
{
}

MovingBgObj::~MovingBgObj()
{
}

void MovingBgObj::Init()
{
	SpriteGo::Init();

	accumTime = 0.f;

	speed = Utils::RandomRange(speedRange.x, speedRange.y);
	sf::Vector2f randomPos(
		Utils::RandomRange(posXRange.x, posXRange.y), 
		Utils::RandomRange(posYRange.x, posYRange.y));

	int rnd = Utils::RandomRange(0, 1);	// 0: L, 1: R
	if (rnd == 0)
	{
		originalPos = leftPos + randomPos;
		SetPosition(originalPos);
		direction = sf::Vector2f(1.f, 0.f);
		SetFlipX(spriteDir.x > 0);
	}
	else
	{
		originalPos = rightPos + randomPos;
		SetPosition(originalPos);
		direction = sf::Vector2f(-1.f, 0.f);
		SetFlipX(spriteDir.x < 0);
	}
}

void MovingBgObj::Release()
{
	SpriteGo::Release();
}

void MovingBgObj::Update(float dt)
{
	SpriteGo::Update(dt);

	accumTime += dt;

	sf::Vector2f pos = GetPosition();
	pos += direction * speed * dt;

	pos.y = originalPos.y + sin(accumTime * widthY)* heightY;

	SetPosition(pos);

	if (pos.x < leftPos.x || pos.x > rightPos.x)
	{
		Init();
	}
}

void MovingBgObj::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void MovingBgObj::SetSpeedRange(sf::Vector2f sRange)
{
	speedRange = sRange;
}

void MovingBgObj::SetLRPos(sf::Vector2f left, sf::Vector2f right)
{
	leftPos = left;
	rightPos = right;
}

void MovingBgObj::SetPosXRange(float min, float max)
{
	posXRange.x = min;
	posXRange.y = max;
}

void MovingBgObj::SetPosYRange(float min, float max)
{
	posYRange.x = min;
	posYRange.y = max;
}

void MovingBgObj::SetMoveY(float w, float h)
{
	widthY = w;
	heightY = h;
}

void MovingBgObj::SetSize(float xSize, float ySize)
{
	SpriteGo::SetSize(xSize, ySize);
}

