#include "stdafx.h"
#include "BlockGo.h"
#include "BouncyBall.h"
#include "InputMgr.h"
#include "ResourceMgr.h"


BlockGo::BlockGo(const std::string n)
	:RectGo(n), blockHP(1), isPlayer(false), itemDrop(false), isPlatform(false)
{

}

BlockGo::~BlockGo()
{
}

void BlockGo::SetPosition(float x, float y)
{
	RectGo::SetPosition(x, y);
	blockUp.SetPosition(GetPosition().x, GetPosition().y - (rectangle.getSize().y / 2) + 1.0f);
	blockDown.SetPosition(GetPosition().x, GetPosition().y + (rectangle.getSize().y / 2) - 0.1f);
	blockLeft.SetPosition(GetPosition().x - (rectangle.getSize().x / 2)- 0.1f, GetPosition().y);
	blockRight.SetPosition(GetPosition().x + (rectangle.getSize().x / 2)- 0.1f, GetPosition().y);
}

void BlockGo::SetPosition(const sf::Vector2f& p)
{
	RectGo::SetPosition(p);
	blockUp.SetPosition(GetPosition().x, GetPosition().y - (rectangle.getSize().y / 2) + 1.0f);
	blockDown.SetPosition(GetPosition().x, GetPosition().y + (rectangle.getSize().y / 2) - 0.1f);
	blockLeft.SetPosition(GetPosition().x - (rectangle.getSize().x / 2) + (rectangle.getSize().x*0.6), GetPosition().y);
	blockRight.SetPosition(GetPosition().x + (rectangle.getSize().x / 2)- (rectangle.getSize().x * 0.6), GetPosition().y);
}


void BlockGo::SetSize(const sf::Vector2f& size)
{
	RectGo::SetSize(size);
	blockUp.SetSize(size.x, 0.2f);
	blockDown.SetSize(size.x, 0.2f);
	blockLeft.SetSize(1.4f, size.y-5.f);
	blockRight.SetSize(1.4f, size.y-5.f);
}

void BlockGo::Init()
{
	RectGo::Init();
}

void BlockGo::Reset()
{
	RectGo::Reset();
}

void BlockGo::Release()
{
	RectGo::Release();
}

void BlockGo::Update(float dt)
{
	RectGo::Update(dt);
}

void BlockGo::Draw(sf::RenderWindow& window)
{
	RectGo::Draw(window);
}


bool BlockGo::BlockNBall(const sf::FloatRect& rect, BouncyBall* ball)
{
	sf::Vector2f rectHalfSize(rect.width / 2.f, rect.height / 2.f);
	sf::Vector2f circleDistance(
		std::abs(ball->GetPosition().x - rect.left - rectHalfSize.x),
		std::abs(ball->GetPosition().y - rect.top - rectHalfSize.y)
	);

	if (circleDistance.x > (rectHalfSize.x + ball->circle.getRadius()) ||
		circleDistance.y > (rectHalfSize.y + ball->circle.getRadius()))
	{
		return false;
	}

	if (circleDistance.x <= rectHalfSize.x ||
		circleDistance.y <= rectHalfSize.y)
	{
		return true;
	}

	float cornerDistanceSq = std::pow(circleDistance.x - rectHalfSize.x, 2) +
		std::pow(circleDistance.y - rectHalfSize.y, 2);

	return cornerDistanceSq <= std::pow(ball->circle.getRadius(), 2);
}

void BlockGo::CheckBlock(BouncyBall* ball)
{
	if (BlockNBall(blockUp.frect,ball) && GetActive())
	{
		ball->Yup();
		if (!isPlayer)
		{
			blockHP--;
		}
	}
	if (BlockNBall(blockDown.frect, ball) && GetActive())
	{
		ball->Ydown();
		if (!isPlayer)
		{
			blockHP--;
		}
	}
	if (BlockNBall(blockLeft.frect, ball) && GetActive())
	{
		ball->Xleft();
		if (!isPlayer)
		{
			blockHP--;
		}
	}
	if (BlockNBall(blockRight.frect, ball) && GetActive())
	{
		ball->Xright();
		if (!isPlayer)
		{
			blockHP--;
		}
	}
}



void BlockGo::SetPlayer()
{
	isPlayer = true;
}

bool BlockGo::isBreak()
{
	return blockHP==0;
}

void BlockGo::SetBlockHp(int hp)
{
	blockHP = hp;
}

bool BlockGo::ItemDrop()
{
	if (itemDrop)
	{
		itemDrop = false;

	}
	return itemDrop;
}

void BlockGo::SetPlatform(bool b)
{
	isPlatform = b;
}

bool BlockGo::IsPlatform()
{
	return isPlatform;
}
