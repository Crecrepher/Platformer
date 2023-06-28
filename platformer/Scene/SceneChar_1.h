#pragma once
#include "Scene.h"

class SceneChar_1 : public Scene
{
protected:
public:
	SceneChar_1();
	virtual ~SceneChar_1() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

