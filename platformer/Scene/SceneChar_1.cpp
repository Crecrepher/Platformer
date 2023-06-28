#include "stdafx.h"
#include "SceneChar_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"

SceneChar_1::SceneChar_1() : Scene(SceneId::Char1)
{
}

SceneChar_1::~SceneChar_1()
{
}

void SceneChar_1::Init()
{
	Release();
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneChar_1::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}

}

void SceneChar_1::Enter()
{
	Scene::Enter();

}

void SceneChar_1::Exit()
{
	Scene::Exit();
}

void SceneChar_1::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneChar_1::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
