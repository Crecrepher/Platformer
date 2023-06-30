#pragma once
#include "SpriteGo.h"


class BlockGo;
class LadderGo;

class PFUnitGo : public SpriteGo
{
private:
	float speed;
	bool isJump;
	bool isDead;
	bool isBlockedSide;
	bool isWallHold;
	bool haveLadder;
	bool climbLadder;

	sf::Vector2f velocity;
	sf::Vector2f gravity;

	int stepCheck;
	int blockSideCheck;
	int wallHoldCheck;
	int haveLadderCheck;

	

public:
	SpriteGo playerSprite;
	sf::Sound jump;


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
	void CheckLadderBlock(LadderGo* ladder);

	void CheckStep();
	void CheckBlockSide();
	void CheckWallHold();
	void CheckLadder();
};

