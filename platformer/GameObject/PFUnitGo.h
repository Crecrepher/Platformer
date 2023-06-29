#pragma once
#include "SpriteGo.h"
#include "BlockGo.h"
#include "FloatRectGo.h"

class PFUnitGo : public SpriteGo
{
private:
	float speed;
	bool isJump;
	bool isDead;
	bool isBlockedSide;
	bool isWallHold;

	sf::Vector2f velocity;
	sf::Vector2f gravity;

	int stepCheck;
	int blockSideCheck;
	int wallHoldCheck;

	FloatRectGo foot;

public:
	PFUnitGo(const std::string n);
	~PFUnitGo();
	virtual void SetPosition(float x, float y)override;
	virtual void SetPosition(const sf::Vector2f& p)override;

	virtual void SetOrigin(Origins origin)override;
	virtual void SetOrigin(float x, float y)override;

	virtual void SetSize(float xSize, float ySize)override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	void Jump(float dt);

	void CheckBlock(BlockGo* block);
	void CheckStep();
	void CheckBlockSide();
	void CheckWallHold();
};

