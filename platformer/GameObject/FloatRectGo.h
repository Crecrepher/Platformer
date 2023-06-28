#pragma once
#include "GameObject.h"
class FloatRectGo : public GameObject
{
private:
	
public:
	sf::FloatRect frect;
	FloatRectGo(const std::string n = "");
	virtual ~FloatRectGo() override;

	virtual void SetSize(const sf::Vector2f& size);
	virtual void SetSize(float x, float y);
	virtual void SetPosition(float x, float y)override;
	virtual void SetPosition(const sf::Vector2f& size)override;

	virtual void Init()override;
	virtual void Reset()override;
	virtual void Release() override;
	virtual void Update(float dt)override;
	virtual void Draw(sf::RenderWindow& window)override;
};

