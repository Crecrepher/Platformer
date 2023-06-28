#pragma once
#include "SpriteGo.h"

class MovingBgObj : public SpriteGo
{
protected:
	float speed;
	sf::Vector2f speedRange;
	sf::Vector2f leftPos;
	sf::Vector2f rightPos;
	sf::Vector2f posXRange;
	sf::Vector2f posYRange;
	sf::Vector2f direction;

	float widthY;
	float heightY;
	float accumTime;

	sf::Vector2f originalPos;

public:
	MovingBgObj(const std::string n);

	~MovingBgObj() override;

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;

	void SetSpeedRange(sf::Vector2f sRange);

	void SetLRPos(sf::Vector2f left, sf::Vector2f right);
	void SetPosXRange(float min, float max);
	void SetPosYRange(float min, float max);
	void SetMoveY(float w, float h);

	void SetSize(float xSize, float ySize) override;
};

