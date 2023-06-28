#include "stdafx.h"
#include "BouncyBall.h"
#include "Framework.h"
#include "InputMgr.h"
BouncyBall::BouncyBall(const std::string n) :CirGo(n), ballCurrentDir(Direction::None)
{
}

BouncyBall::~BouncyBall()
{
}

void BouncyBall::Init()
{
	CirGo::Init();
	SetOrigin(Origins::MC);
	int rnd = Utils::RandomRange(0, 1);
	ballCurrentDir = Direction::Right;
	if (rnd == 0)
	{
		rnd--;
		ballCurrentDir = Direction::Left;
	}
	direction = sf::Vector2f(rnd, -1.f);
	//SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f,
	//	FRAMEWORK.GetWindowSize().y * 0.4f);
}

void BouncyBall::Reset()
{
	CirGo::Reset();
	Init();
	lifelost = 0;
}

void BouncyBall::Release()
{
	CirGo::Release();
}

void BouncyBall::Update(float dt)
{
	CirGo::Update(dt);
	SetOrigin(Origins::MC);
	sf::Vector2f pos = GetPosition();
	pos.x += direction.x * speed * dt;
	pos.y += direction.y * speed * dt;
	SetPosition(pos);

	if (pos.x < ballRadius)
	{
		Xright();
	}
	else if (pos.x > FRAMEWORK.GetWindowSize().x - ballRadius)
	{
		Xleft();
	}
	if (pos.y < ballRadius)
	{
		Ydown();
	}
	if (pos.y > FRAMEWORK.GetWindowSize().y + ballRadius)
	{
		Init();
		lifelost++;
		isDead = true;
	}

	else if (direction.x > 0)
	{
		ballCurrentDir = Direction::Right;
	}
	else if (direction.x < 0)
	{
		ballCurrentDir = Direction::Left;
	}
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return) ||
		INPUT_MGR.GetKeyDown(sf::Keyboard::Space))
	{
		if (isDead = true)
		{
			isDead = false;
		}
		
	}
}

void BouncyBall::Draw(sf::RenderWindow& window)
{
	CirGo::Draw(window);
}

void BouncyBall::SetBallSize(float radius)
{
	circle.setRadius(radius);
	ballRadius = radius;
}

void BouncyBall::Xbounce()
{
	direction.x *= -1;
}

void BouncyBall::Ybounce()
{
	direction.y *= -1;
}

void BouncyBall::Xleft()
{
	if (direction.x > 0)
	{
		direction.x *= -1;
	}
}

void BouncyBall::Yup()
{
	if (direction.y > 0)
	{
		direction.y *= -1;
	}
}

void BouncyBall::Xright()
{
	if (direction.x < 0)
	{
		direction.x *= -1;
	}
}

void BouncyBall::Ydown()
{
	if (direction.y < 0)
	{
		direction.y *= -1;
	}
}

sf::Vector2f BouncyBall::GetDir() const
{
	return direction;
}

int BouncyBall::LifeLost() const
{
	return lifelost;
}

bool BouncyBall::IsDead() const
{
	return isDead;
}

