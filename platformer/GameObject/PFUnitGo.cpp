#include "stdafx.h"
#include "PFUnitGo.h"
#include "InputMgr.h"
#include "LadderGo.h"
#include "FloatRectGo.h"
#include "BlockGo.h"

PFUnitGo::PFUnitGo(const std::string n) : SpriteGo(n), speed(500),
isJump(true), isDead(false), velocity(0.f, 1000.f), gravity(0.f, 3000.f),
isBlockedSide(false), stepCheck(0), blockSideCheck(0), wallHoldCheck(0), isWallHold(false),
haveLadder(false), climbLadder(false), isPlatformDown(false)
{

}

PFUnitGo::~PFUnitGo()
{
}

void PFUnitGo::SetPosition(float x, float y)
{
	SpriteGo::SetPosition(x, y);
	playerSprite.SetPosition(x, y - (GetSize().y * 0.3 / 2));
}

void PFUnitGo::SetPosition(const sf::Vector2f& p)
{
	SpriteGo::SetPosition(p);
	playerSprite.SetPosition(p.x,p.y - (GetSize().y*0.3/2));
}

void PFUnitGo::SetOrigin(Origins origin)
{
	SpriteGo::SetOrigin(origin);
	playerSprite.SetOrigin(Origins::MC);
}

void PFUnitGo::SetOrigin(float x, float y)
{
	SpriteGo::SetOrigin(x, y);
	playerSprite.SetOrigin(Origins::MC);
}

void PFUnitGo::SetSize(float xSize, float ySize)
{
	SpriteGo::SetSize(xSize, ySize);
	playerSprite.SetSize(xSize, ySize);
}

void PFUnitGo::Init()
{
	SpriteGo::Init();
	stepCheck = 0;
	blockSideCheck = 0;
	wallHoldCheck = 0;
	haveLadderCheck = 0;
	gravity.y = 3000;
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
	Init();
	

	if ((!isBlockedSide || !isWallHold)&& !climbLadder)
	{
		if (INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			if (velocity.x > 0.6)
			{
				velocity.x = 0.5;
			}
			else if (velocity.x > -0.5f)
			{
				velocity.x -= 0.002f;
			}
			
			SetPosition(GetPosition().x + (velocity.x *speed * dt), GetPosition().y);
			playerSprite.SetFlipX(false);
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			if (velocity.x < -0.6)
			{
				velocity.x = -0.5;
			}
			else if (velocity.x < 0.5f)
			{
				velocity.x += 0.002f;
			}
			SetPosition(GetPosition().x + (velocity.x * speed * dt), GetPosition().y);
			playerSprite.SetFlipX(true);
		}
		else if (velocity.x > 0)
		{
			velocity.x -= 0.001f;
		}
		else if (velocity.x < 0)
		{
			velocity.x += 0.001f;
		}
		SetPosition(GetPosition().x + (velocity.x * speed * dt), GetPosition().y);
	}
	else
	{
		if (velocity.x > 0)
		{
			velocity.x -= 0.01f;
		}
		else if (velocity.x < 0)
		{
			velocity.x += 0.01f;
		}
	
		SetPosition(GetPosition().x + (velocity.x * speed * dt), GetPosition().y);
	}
	
	if (isWallHold && isJump && velocity.y>0)
	{
		velocity.x = 0;
		if (velocity.y > 300.0f)
		{
			velocity.y = 300;
		}
		gravity.y = 200;
		if (INPUT_MGR.GetKey(sf::Keyboard::Left) && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			SetPosition(GetPosition().x + 3.0f, GetPosition().y);
			velocity += sf::Vector2f(0.5f, 0.f);
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Right) && INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
		{
			SetPosition(GetPosition().x - 3.0f, GetPosition().y);
			velocity -= sf::Vector2f(0.5f, 0.f);
		}
	}
	else if (isWallHold && !isJump)
	{
		if (INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			velocity.x += 0.01;
		}
		else if (INPUT_MGR.GetKey(sf::Keyboard::Right))
		{
			velocity.x -= 0.01;
		}
	}


	if (haveLadder)
	{
		if (INPUT_MGR.GetKey(sf::Keyboard::Up) ||
			INPUT_MGR.GetKey(sf::Keyboard::Down))
		{
			climbLadder = true;
		}
		if (climbLadder)
		{
			playerSprite.sprite.setRotation(0);
			gravity.y = 0;
			velocity.x = 0;
			velocity.y = 0;
			if (INPUT_MGR.GetKey(sf::Keyboard::Up))
			{
				SetPosition(GetPosition().x, GetPosition().y - (700.f * dt));
			}
			else if (INPUT_MGR.GetKey(sf::Keyboard::Down))
			{
				SetPosition(GetPosition().x, GetPosition().y + (700.f * dt));
			}
		}
	}
	else
	{
		climbLadder = false;
	}


	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Space) && ((!isJump|| isWallHold)||climbLadder)&& !isPlatformDown)
	{
		velocity.y = -1000.f;
		isJump = true;
		climbLadder = false;
		jump.play();
	}
	Jump(dt);
	if (!isJump)
	{
		playerSprite.sprite.rotate(velocity.x * dt * 2000);
	}

}

void PFUnitGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
	playerSprite.Draw(window);
}

void PFUnitGo::Jump(float dt)
{
	if (isJump)
	{
		if (velocity.y < 700.0f)
		{
			velocity += gravity * dt;
		}
		if (!isWallHold && !climbLadder)
		{
			playerSprite.sprite.rotate(dt * -10000 * playerSprite.sprite.getScale().x);
		}
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
	
	if (block->blockLeft.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		velocity.x = 0.f;
		if ((GetPosition().x + GetSize().x / 2) > (block->rectangle.getPosition().x - block->rectangle.getSize().x / 2))
		{
			sprite.setPosition((block->rectangle.getPosition().x )- (block->rectangle.getSize().x / 2 )- (GetSize().x*0.3 / 2)+0.2f, GetPosition().y);
		}
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
		velocity.x = 0.f;
		if ((GetPosition().x - GetSize().x / 2) < (block->rectangle.getPosition().x + block->rectangle.getSize().x / 2))
		{
			sprite.setPosition((block->rectangle.getPosition().x) + (block->rectangle.getSize().x / 2) + (GetSize().x * 0.3 / 2) - 0.2f, GetPosition().y);
		}
		if (!INPUT_MGR.GetKey(sf::Keyboard::Right) || INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			blockSideCheck++;
		}
		if (INPUT_MGR.GetKey(sf::Keyboard::Left))
		{
			wallHoldCheck++;
		}
	}
	else if (block->blockDown.frect.intersects(sprite.getGlobalBounds()) && !block->IsPlatform())
	{
		if (velocity.y < 0)
		{
			velocity.y *= -1.f;
		}
	}

}

void PFUnitGo::CheckLadderBlock(LadderGo* ladder)
{
	if (ladder->rectangle.getGlobalBounds().intersects(sprite.getGlobalBounds()))
	{
		haveLadderCheck++;
		if (velocity.y > 0 && GetPosition().y - 5.f <= ladder->rectangle.getGlobalBounds().top)
		{
			stepCheck++;
		}

		if (climbLadder)
		{
			SetPosition(ladder->GetPosition().x, GetPosition().y);
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

void PFUnitGo::CheckLadder()
{
	haveLadder = haveLadderCheck > 0;
}

bool PFUnitGo::IsPlatformDown(BlockGo* block)
{
	return block->IsPlatform() && INPUT_MGR.GetKey(sf::Keyboard::Down) && INPUT_MGR.GetKeyDown(sf::Keyboard::Space);
}
