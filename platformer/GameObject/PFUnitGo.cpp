#include "stdafx.h"
#include "PFUnitGo.h"
#include "InputMgr.h"

PFUnitGo::PFUnitGo(const std::string n) : SpriteGo(n), speed(500),
isJump(true), isDead(false), velocity(0.f, 1000.f), gravity(0.f, 3000.f),
isBlockedSide(false), stepCheck(0), blockSideCheck(0), wallHoldCheck(0), isWallHold(false)
{

}

PFUnitGo::~PFUnitGo()
{
}

void PFUnitGo::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	foot.SetPosition(x, y-1.0f);
}

void PFUnitGo::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	foot.SetPosition(p.x,p.y-1.0f);
}

void PFUnitGo::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
}

void PFUnitGo::SetOrigin(float x, float y)
{
	SpriteGo::SetOrigin(x, y);
}

void PFUnitGo::SetSize(float xSize, float ySize)
{
	SpriteGo::SetSize(xSize, ySize);
	foot.SetSize(GetSize().x, 10.0f);
}

void PFUnitGo::Init()
{
	SpriteGo::Init();
	
}

void PFUnitGo::Reset()
{
	SpriteGo::Reset();
}

void PFUnitGo::Release()
{
	SpriteGo::Release();
}

void PFUnitGo::Update(float dt)
{
	SpriteGo::Update(dt);
	//foot.SetSize(GetSize().x,2.f);
	//foot.SetPosition(GetPosition().x
	//	, sprite.getLocalBounds().top + sprite.getLocalBounds().height - 2.f);
	stepCheck = 0;
	blockSideCheck = 0;
	wallHoldCheck = 0;

	if (!isBlockedSide || !isWallHold)
	{
		if (INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			SetPosition(GetPosition().x - (speed * dt), GetPosition().y);
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			SetPosition(GetPosition().x + (speed * dt), GetPosition().y);
		}
	}
	


	
	if (isWallHold && isJump && velocity.y>0)
	{
		velocity.y = 0;
		if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			isWallHold = false;
		}
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		velocity = sf::Vector2f(0.f, -1000.f);
		isJump = true;
	}

	Jump(dt);

}

void PFUnitGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void PFUnitGo::Jump(float dt)
{
	if (isJump)
	{
		velocity += gravity * dt;
		SetPosition(position + velocity * dt);
	}
}

void PFUnitGo::CheckBlock(BlockGo* block)
{
	if (block->blockUp.frect.intersects(sprite.getGlobalBounds()))
	{
		if (velocity.y > 0 && GetPosition().y - 5.f <= block->GetPosition().y - block->rectangle.getSize().y / 2)
		{
			stepCheck++;
		}
	}
	else if (block->blockLeft.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		if (!INPUT_MGR.GetKey(sf::Keyboard::Left) || INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			blockSideCheck++;
		}
		if (INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			wallHoldCheck++;
		}
	}
	else if (block->blockRight.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		if (!INPUT_MGR.GetKey(sf::Keyboard::Right) || INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			blockSideCheck++;
		}
		if (INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			wallHoldCheck++;
		}
	}
	if (block->blockDown.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		if (velocity.y < 0)
		{
			velocity.y *= -1.f;
		}
	}
}

void PFUnitGo::CheckStep()
{
	if (stepCheck > 0)
	{
		isJump = false;
	}
	else
	{
		isJump = true;
	}
}

void  PFUnitGo::CheckBlockSide()
{
	if (blockSideCheck > 0)
	{
		isBlockedSide = true;
	}
	else
	{
		isBlockedSide = false;
	}
}

void PFUnitGo::CheckWallHold()
{
	if (wallHoldCheck>0)
	{
		isWallHold = true;
	}
	else
	{
		isWallHold = false;
	}
}
