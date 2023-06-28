#pragma once
#include "Scene.h"
#include "BlockGo.h"
#include "EffectGo.h"
#include <sstream>
class SceneGame : public Scene
{
protected:

public:
	SceneGame();
	virtual ~SceneGame() override;

	virtual void Init() override;
	virtual void Release() override;

	virtual void Enter() override;
	virtual void Exit() override;

	virtual void Update(float dt) override;
	virtual void Draw(sf::RenderWindow& window) override;
};

