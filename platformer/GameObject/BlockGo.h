#pragma once
#include "RectGo.h"
#include "FloatRectGo.h"
#include "RectGo.h"

class BouncyBall;

class BlockGo : public RectGo
{
private:
	bool itemDrop;
	bool isPlayer;
	int blockHP;
	bool isPlatform;


public:
	FloatRectGo blockUp;
	FloatRectGo blockDown;
	FloatRectGo blockLeft;
	FloatRectGo blockRight;
	


	BlockGo(const std::string n = "");
	virtual ~BlockGo() override;

	virtual void SetPosition(float x, float y) override;
	virtual void SetPosition(const sf::Vector2f& p)override;

	virtual void SetSize(const sf::Vector2f& size)override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	bool BlockNBall(const sf::FloatRect& rect, BouncyBall* ball);
	void CheckBlock(BouncyBall* ball);

	void SetPlayer();
	bool isBreak();
	void SetBlockHp(int hp);
	bool ItemDrop();

	void SetPlatform(bool b);
	bool IsPlatform();
};

