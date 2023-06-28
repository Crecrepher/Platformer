#include "stdafx.h"
#include "Scene.h"
#include "GameObject.h"
#include "ResourceMgr.h"
#include "GameObject.h"

Scene::Scene(SceneId id)
	:sceneId(id)
{
}

Scene::~Scene()
{
	Release();
}

GameObject* Scene::FindGo(const std::string& name)
{
	auto compare = [name](GameObject* go) {return go->GetName() == name; };
	auto it = std::find_if(gameObjects.begin(), gameObjects.end(), compare);
	//람다 표현식 : compare에서 true가 나오는 녀석이 나타날때까지 돌리고 찾아서 나오면 돌려줌
	//함수의 레퍼런스라고 보면 됨
	if (it == gameObjects.end())
	{
		return nullptr;
	}
	return *it;

	//아래의 방법도 가능
	//for (auto go : gameObjects)
	//{
	//	if (go->GetName() == name)
	//	{
	//		return go;
	//	}
	//}

	//return nullptr;
}

void Scene::FindGos(std::list<GameObject*> list, const std::string& name)
{
	//list.clear();
	for (auto go : gameObjects)
	{
		if (go->GetName() == name)
		{
			list.push_back(go);
		}
	}
}

bool Scene::Exist(GameObject* go)
{
	return std::find(gameObjects.begin(), gameObjects.end(), go) != gameObjects.end();
}

void Scene::AddGo(GameObject* go)
{
	if (!Exist(go))
	{
		gameObjects.push_back(go);
	}
}

void Scene::RemoveGo(GameObject* go)
{
	gameObjects.remove(go);
	//delete go;
}

void Scene::SortGos()
{
	gameObjects.sort([](GameObject* lhs, GameObject* rhs) {
		if (lhs->sortLayer != rhs->sortLayer)
		{
			return lhs->sortLayer < rhs->sortLayer;
		}
		return lhs->sortOrder < rhs->sortOrder;
		});
}

void Scene::Enter()
{
	RESOURCE_MGR.Load(resources);

	for (auto go : gameObjects)
	{
		go->Reset();
	}
}

void Scene::Exit()
{
	RESOURCE_MGR.Unload(resources);
}

void Scene::Update(float dt)
{
	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Update(dt);
		}
	}
}

void Scene::Draw(sf::RenderWindow& window)
{
	SortGos();

	for (auto go : gameObjects)
	{
		if (go->GetActive())
		{
			go->Draw(window);
		}
	}
}
