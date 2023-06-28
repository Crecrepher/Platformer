#include "stdafx.h"
#include "SceneGame.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"

SceneGame::SceneGame() : Scene(SceneId::Game)
{
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();
	RESOURCE_MGR.Load(ResourceTypes::Texture, "graphics/player4.png");
}

void SceneGame::Exit()
{
	Scene::Exit();
	RESOURCE_MGR.Unload(ResourceTypes::Texture, "graphics/player4.png");
}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

	sf::Sprite sprite;
	sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/player4.png"));
	window.draw(sprite);
}
