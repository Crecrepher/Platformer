#include "stdafx.h"

#include "SceneMgr.h"
#include "Scene.h"
#include "SceneTitile.h"
#include "SceneMenu.h"
#include "SceneGame_1.h"

#include "ResourceMgr.h"

void SceneMgr::ChangeScene(SceneId id)
{
	scenes[(int)currentSceneId]->Exit();
	currentSceneId = id;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
}

void SceneMgr::Init()
{
	if (!scenes.empty())
	{
		return;
	}
			
	scenes.push_back(new SceneTitile());
	scenes.push_back(new SceneMenu());
	scenes.push_back(new SceneGame());

	for (auto scene : scenes)
	{
		scene->Init();
	}

	currentSceneId = startSceneId;
	currentScene = scenes[(int)currentSceneId];
	currentScene->Enter();
	bgm.sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/bgm.wav"));
	bgm.sound.setLoop(true);
}

void SceneMgr::Release()
{
	if (scenes.empty())
	{
		return;
	}

	for (auto scene : scenes)
	{
		scene->Release();
		delete scene;
	}
	scenes.clear();

	currentSceneId = SceneId::None;
	currentScene = nullptr;
}

void SceneMgr::Update(float dt)
{
	timer += dt;
	if (timer >= 1.33f)
	{
		timeFlip = !timeFlip;
		timer = 0.f;
	}

	if (bgmPlay)
	{
		bgm.sound.play();
		bgmPlay = false;
	}
	scenes[(int)currentSceneId]->Update(dt);
}

void SceneMgr::Draw(sf::RenderWindow& window)
{
	scenes[(int)currentSceneId]->Draw(window);
}

float SceneMgr::TimerTime() const
{
	return timer;
}

bool SceneMgr::TimeBaseFliper() const
{
	return timeFlip;
}

void SceneMgr::BgmOn()
{
	bgmPlay = true;
}

void SceneMgr::BgmOff()
{
	bgm.sound.stop();
}
