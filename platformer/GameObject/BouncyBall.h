#pragma once
#include "CirGo.h"

class BouncyBall : public CirGo
{
private:

	float speed = 500;
	int lifelost = 0;

	bool isDead = true;

public:
	float ballRadius;
	sf::Vector2f direction;
	Direction ballCurrentDir;
	BouncyBall(const std::string n = "");
	virtual ~BouncyBall() override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;

	void SetBallSize(float radius);
	void Xbounce();
	void Ybounce();
	void Xleft();
	void Yup();
	void Xright();
	void Ydown();

	sf::Vector2f GetDir() const;
	int LifeLost() const;

	bool IsDead() const;
};

