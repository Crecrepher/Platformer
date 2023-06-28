#include "stdafx.h"
#include "SceneChar_2.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"

SceneChar_2::SceneChar_2() : Scene(SceneId::Title)
{
}

SceneChar_2::~SceneChar_2()
{
}

void SceneChar_2::Init()
{
	Release();
	
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneChar_2::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}

}

void SceneChar_2::Enter()
{
	Scene::Enter();

}

void SceneChar_2::Exit()
{
	Scene::Exit();
}

void SceneChar_2::Update(float dt)
{
	Scene::Update(dt);
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
	}
}

void SceneChar_2::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
