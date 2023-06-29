#include "stdafx.h"
#include "SceneTitile.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "SpriteGo.h"
#include "TextGo.h"
#include "SoundGo.h"
#include "Framework.h"

SceneTitile::SceneTitile() : Scene(SceneId::Title)
{
	//resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/timber_icon.png"));
	//여기서만 쓰는거
}

SceneTitile::~SceneTitile()
{
}

void SceneTitile::Init()
{
	//계속써도되는거 add
	Release();
	AddGo(new SpriteGo("Icon"));
	AddGo(new TextGo("Text"));
	AddGo(new SoundGo("MoveSound"));

	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneTitile::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}

}

void SceneTitile::Enter()
{
	Scene::Enter();
	SpriteGo* findSGo = (SpriteGo*)FindGo("Icon");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/timber_icon.png"));
	findSGo->SetOrigin(Origins::MC);
	findSGo->SetPosition(FRAMEWORK.GetWindowSize().x / 2.f, FRAMEWORK.GetWindowSize().y / 3.f);
	findSGo->sortLayer = 1;


	TextGo* findTGo = (TextGo*)FindGo("Text");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/KOMIKAP_.ttf"));
	findTGo->text.setString("PRESS ENTER");
	findTGo->text.setCharacterSize(125);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::MC);
	findTGo->text.setPosition(FRAMEWORK.GetWindowSize().x * 0.5f, FRAMEWORK.GetWindowSize().y * 0.7f);
	findTGo->sortLayer = 1;

	SoundGo* soundChop = (SoundGo*)FindGo("MoveSound");
	soundChop->sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/chop.wav"));
	//생기고 사라질거 샛 택스쳐
}

void SceneTitile::Exit()
{
	Scene::Exit();
}

void SceneTitile::Update(float dt)
{
	Scene::Update(dt);

	SpriteGo* findGo = (SpriteGo*)FindGo("Icon");
	findGo->SetSize(1.8f + (SCENE_MGR.TimerTime() / 10.f),
		1.8f + (SCENE_MGR.TimerTime() / 10.f));

	TextGo* findTGo = (TextGo*)FindGo("Text");
	findTGo->SetActive(SCENE_MGR.TimeBaseFliper());

	SoundGo* soundChop = (SoundGo*)FindGo("MoveSound");
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Enter))
	{
		SCENE_MGR.ChangeScene(SceneId::Menu);
		soundChop->sound.play();
	}
}

void SceneTitile::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
}
