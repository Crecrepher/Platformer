#pragma once
#include "SpriteGo.h"

class EffectGo : public SpriteGo
{
protected:
	sf::Vector2f velocity;
	sf::Vector2f gravity;

	float duration;
	float timer;
	bool isFire;
public:
	EffectGo(const std::string& n = "");
	~EffectGo();

	void Fire(sf::Vector2f v);

	virtual void Init() override;
	virtual void Release() override;
	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
	void SetSize(float xSize, float ySize) override;
};

