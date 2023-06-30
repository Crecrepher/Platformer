#include "EffectGo.h"
#include "stdafx.h"
EffectGo::EffectGo(const std::string& n)
	: SpriteGo(n), gravity(0.f, 3000.f), duration(3.f), timer(0.f),isFire(false)
{
	SetOrigin(Origins::MC);
}

EffectGo::~EffectGo()
{
}

void EffectGo::Fire(sf::Vector2f v)
{
	velocity = v;
	isFire = true;
}

void EffectGo::Init()
{
	SpriteGo::Init();
	
	timer = 0.f;
}

void EffectGo::Release()
{
	SpriteGo::Release();
}

void EffectGo::Update(float dt)
{
	if (isFire)
	{
		timer += dt;
		if (timer > duration)
		{
			SetActive(false);
			return;
		}
		velocity += gravity * dt;
		SetPosition(position + velocity * dt);
	}
	SpriteGo::Update(dt);
	

}

void EffectGo::Draw(sf::RenderWindow& window)
{
	SpriteGo::Draw(window);
}

void EffectGo::SetSize(float xSize, float ySize)
{
	SpriteGo::SetSize(xSize, ySize);
}
