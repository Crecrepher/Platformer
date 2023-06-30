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

	SceneId startSceneId = SceneId::Title;

	float timer = 0.f;
	bool timeFlip;

	SoundGo bgm;
	bool bgmPlay = false;

public:
	void ChangeScene(SceneId id);

	void Init();
	void Release();

	void Update(float dt);
	void Draw(sf::RenderWindow& window);
	float TimerTime() const;
	bool TimeBaseFliper() const;
	void BgmOn();
	void BgmOff();
};

#define SCENE_MGR (SceneMgr::Instance())
