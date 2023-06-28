#pragma once
#include "Singleton.h"
#include "SoundGo.h"

class Scene;

class SceneMgr : public Singleton<SceneMgr>
{
	friend Singleton<SceneMgr>;

protected:
	SceneMgr() = default;
	virtual	~SceneMgr() = default;

	std::vector<Scene*> scenes;
	SceneId currentSceneId = SceneId::None;
	Scene* currentScene = nullptr;

	SceneId startSceneId = SceneId::Game1;

	float timer = 0.f;
	bool timeFlip;

	SoundGo bgm;
	bool bgmPlay;

public:
	void ChangeScene(SceneId id);

	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	float TimerTime() const;
	bool TimeBaseFliper() const;
};

#define SCENE_MGR (SceneMgr::Instance())
