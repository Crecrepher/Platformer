#pragma once
#include "Scene.h"

class SceneMenu : public Scene
{
protected:
	int menuIndex;
	float closeTimer;
	bool isClose;
public:
	SceneMenu();
	virtual ~SceneMenu() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

