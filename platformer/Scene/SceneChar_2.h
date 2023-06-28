#pragma once
#include "Scene.h"

class SceneChar_2 : public Scene
{
protected:
public:
	SceneChar_2();
	virtual ~SceneChar_2() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

