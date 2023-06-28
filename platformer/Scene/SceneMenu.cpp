#include "stdafx.h"
#include "SceneMenu.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "EffectGo.h"
#include "RectGo.h"
#include "SoundGo.h"
#include "Framework.h"


SceneMenu::SceneMenu() : Scene(SceneId::Menu), 
menuIndex(0), closeTimer(0.f), isClose(false)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/b1.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/b2.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/b3.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/chop_screen.png"));
}

SceneMenu::~SceneMenu()
{
}

void SceneMenu::Init()
{
	Release();
	
	AddGo(new EffectGo("Icon"));
	AddGo(new SpriteGo("Back"));
	AddGo(new SpriteGo("Menu1"));
	AddGo(new SpriteGo("Menu2"));
	AddGo(new SpriteGo("Menu3"));
	AddGo(new SpriteGo("ChopScreen"));
	AddGo(new RectGo("MenuSelector"));
	AddGo(new SoundGo("MoveSound"));
	AddGo(new SoundGo("ExitSound"));
	for (auto go : gameObjects)
	{
		go->Init();
	}
}

void SceneMenu::Release()
{
	for (auto go : gameObjects)
	{
		//go->Release();
		delete go;
	}
	//RESOURCE_MGR.GetSoundBuffer
}

void SceneMenu::Enter()
{
	Scene::Enter();
	EffectGo* findEGo = (EffectGo*)FindGo("Icon");
	findEGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/timber_icon.png"));
	findEGo->SetOrigin(Origins::MC);
	findEGo->SetPosition(FRAMEWORK.GetWindowSize().x / 2.f, FRAMEWORK.GetWindowSize().y / 3.f);
	findEGo->sortLayer = 1;

	SpriteGo* findSGo;
	findSGo = (SpriteGo*)FindGo("Back");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/title.png"));
	findSGo->SetPosition(0.f, 0.f);
	findSGo->SetSize(0.7f, 0.7f);
	findSGo->sortLayer = 0;

	findSGo = (SpriteGo*)FindGo("ChopScreen");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/chop_screen.png"));
	findSGo->SetOrigin(Origins::TC);
	findSGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f, 0.f);
	findSGo->SetActive(false);
	findSGo->SetSize(0.7f, 0.7f);
	findSGo->sortLayer = 4;

	findSGo = (SpriteGo*)FindGo("Menu3");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/b3.png"));
	findSGo->SetOrigin(Origins::MC);
	findSGo->SetPosition(FRAMEWORK.GetWindowSize().x *0.75f,
		FRAMEWORK.GetWindowSize().y*0.8f);
	findSGo->SetSize(0.7f, 0.7f);
	findSGo->sortLayer = 3;

	findSGo = (SpriteGo*)FindGo("Menu2");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/b2.png"));
	findSGo->SetOrigin(Origins::MC);
	findSGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5f,
		FRAMEWORK.GetWindowSize().y * 0.8f);
	findSGo->SetSize(0.7f, 0.7f);
	findSGo->sortLayer = 3;

	findSGo = (SpriteGo*)FindGo("Menu1");
	findSGo->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/b1.png"));
	findSGo->SetOrigin(Origins::MC);
	findSGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.25f,
		FRAMEWORK.GetWindowSize().y * 0.8f);
	findSGo->SetSize(0.7f, 0.7f);
	findSGo->sortLayer = 3;

	RectGo* findRGo = (RectGo*)FindGo("MenuSelector");
	findRGo->rectangle.setSize(sf::Vector2f(
		findSGo->GetSize().x* 0.74f,
		findSGo->GetSize().y * 0.74f));
	findRGo->SetOrigin(Origins::MC);
	findRGo->SetPosition(findSGo->GetPosition());
	findRGo->rectangle.setFillColor(sf::Color::Green);
	findRGo->sortLayer = 2;

	SoundGo* soundGo = (SoundGo*)FindGo("MoveSound");
	soundGo->sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/chop.wav"));
	
	soundGo = (SoundGo*)FindGo("ExitSound");
	soundGo->sound.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/death.wav"));
}

void SceneMenu::Exit()
{
	Scene::Exit();
}

void SceneMenu::Update(float dt)
{
	Scene::Update(dt);

	//아이콘 애니메이션
	EffectGo* findGo = (EffectGo*)FindGo("Icon");
	findGo->SetSize(1.8 + (SCENE_MGR.TimerTime() / 10),
		1.8 + (SCENE_MGR.TimerTime() / 10));

	//메뉴선택
	RectGo* findRGo = (RectGo*)FindGo("MenuSelector");
	SoundGo* sound = (SoundGo*)FindGo("MoveSound");
	if (menuIndex > 0 && INPUT_MGR.GetKeyDown(sf::Keyboard::Left)) //왼쪽 방향키
	{
		menuIndex--;
		findRGo->SetPosition
		(findRGo->GetPosition().x 
			- (FRAMEWORK.GetWindowSize().x * 0.25f),
			findRGo->GetPosition().y);
		sound->sound.play();
	}
	else if (menuIndex < 2 && INPUT_MGR.GetKeyDown(sf::Keyboard::Right)) //오른쪽 방향키
	{
		menuIndex++;
		findRGo->SetPosition
		(findRGo->GetPosition().x 
			+ (FRAMEWORK.GetWindowSize().x * 0.25f),
			findRGo->GetPosition().y);
		sound->sound.play();
	}

	//메뉴 선택
	EffectGo* icon = (EffectGo*)FindGo("Icon");
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Return))
	{
		sound->sound.play();
		switch (menuIndex)
		{
		case 0: //1인 플레이
			SCENE_MGR.ChangeScene(SceneId::Game1);
			break;

		case 1: //2인 플레이
			SCENE_MGR.ChangeScene(SceneId::Game1);
			break;
		case 2: //게임 종료
			SpriteGo * chopScreen = (SpriteGo*)FindGo("ChopScreen");
			chopScreen->SetActive(true);
			sound = (SoundGo*)FindGo("ExitSound");
			icon->Fire(sf::Vector2f(-1000.f, -1000.f));
			sound->sound.play();
			isClose = true;
			break;
		}
	}
	if (isClose)
	{
		closeTimer += dt;
	}

	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.ChangeScene(SceneId::Title);
		sound->sound.play();
	}
}

void SceneMenu::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);
	if (closeTimer >= 2.f)
	{
		window.close();
	}
}
