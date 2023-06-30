#include "stdafx.h"
#include "SceneGame_1.h"
#include "SceneMgr.h"
#include "InputMgr.h"
#include "ResourceMgr.h"
#include "GameObject.h"
#include "Framework.h"

#include "PFUnitGo.h"
#include "TextGo.h"
#include "LadderGo.h"


SceneGame::SceneGame() : Scene(SceneId::Game1)
{
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/player4.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Texture, "graphics/player_sprite.png"));
	resources.push_back(std::make_tuple(ResourceTypes::Sound, "sound/jump.wav"));
	resources.push_back(std::make_tuple(ResourceTypes::Font, "fonts/neodgm.ttf"));
}

SceneGame::~SceneGame()
{
}

void SceneGame::Init()
{
	Release();
	AddGo(new PFUnitGo("Player"));
	AddGo(new TextGo("Info"));
	AddGo(new LadderGo("Ladder"));
	for (int i = 0; i < 9; i++)
	{
		std::string str = "Block" + std::to_string(i);
		AddGo(new BlockGo(str));
	}

	for (auto go : gameObjects)
	{
		go->Init();
	}


}

void SceneGame::Release()
{
	for (auto go : gameObjects)
	{
		delete go;
	}
}

void SceneGame::Enter()
{
	Scene::Enter();

	TextGo* findTGo = (TextGo*)FindGo("Info");
	findTGo->text.setFont(*RESOURCE_MGR.GetFont("fonts/neodgm.ttf"));
	findTGo->text.setString("TEST PUFFER FISH ROOM");
	findTGo->text.setCharacterSize(75);
	findTGo->text.setFillColor(sf::Color::White);
	Utils::SetOrigin(findTGo->text, Origins::TL);
	findTGo->text.setPosition(50.f,20.f);

	//위
	std::string str = "Block0";
	BlockGo* findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(FRAMEWORK.GetWindowSize().x, 30.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5,
		findBGo->rectangle.getSize().y/2);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 2;

	//아래
	str = "Block1";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(FRAMEWORK.GetWindowSize().x, 30.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5,
		FRAMEWORK.GetWindowSize().y -(findBGo->rectangle.getSize().y / 2));
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 2;

	//왼쪽
	str = "Block2";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(30.f, FRAMEWORK.GetWindowSize().y));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(findBGo->rectangle.getSize().x / 2,
		FRAMEWORK.GetWindowSize().y*0.5);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	//오른쪽
	str = "Block3";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(30.f, FRAMEWORK.GetWindowSize().y));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x - (findBGo->rectangle.getSize().x / 2),
		FRAMEWORK.GetWindowSize().y * 0.5);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	//나머지블록들
	str = "Block4";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f,300.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x*0.2,
		FRAMEWORK.GetWindowSize().y * 0.8);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	str = "Block5";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 300.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.8,
		FRAMEWORK.GetWindowSize().y * 0.8);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	str = "Block6";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(200.f, 100.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.35,
		FRAMEWORK.GetWindowSize().y * 0.35);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	str = "Block7";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(200.f, 100.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.65,
		FRAMEWORK.GetWindowSize().y * 0.35);
	findBGo->rectangle.setFillColor(sf::Color::Green);
	findBGo->SetPlatform(true);
	findBGo->sortLayer = 1;

	str = "Block8";
	findBGo = (BlockGo*)FindGo(str);
	findBGo->SetSize(sf::Vector2f(100.f, 30.f));
	findBGo->SetOrigin(Origins::MC);
	findBGo->SetPosition(FRAMEWORK.GetWindowSize().x * 0.65,
		FRAMEWORK.GetWindowSize().y * 0.5);
	findBGo->rectangle.setFillColor(sf::Color::White);
	findBGo->sortLayer = 1;

	findBGo = (BlockGo*)FindGo("Block1");
	PFUnitGo* findPlayer = (PFUnitGo*)FindGo("Player");
	findPlayer->sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/player4.png"));
	findPlayer->playerSprite.sprite.setTexture(*RESOURCE_MGR.GetTexture("graphics/player_sprite.png"));
	findPlayer->SetSize(0.3f, 0.3f);
	findPlayer->SetOrigin(Origins::BC);
	findPlayer->SetPosition(findBGo->GetPosition().x, 
		findBGo->GetPosition().y + (findBGo->rectangle.getSize().y / 2)
		- findPlayer->GetSize().y);
	findPlayer->sortLayer = 2;
	findPlayer->playerSprite.sortLayer = 3;
	findPlayer->jump.setBuffer(*RESOURCE_MGR.GetSoundBuffer("sound/jump.wav"));

	LadderGo* ladder = (LadderGo*)FindGo("Ladder");
	ladder->SetSize(sf::Vector2f(50.f, 430.f));
	ladder->SetOrigin(Origins::MC);
	ladder->SetPosition(FRAMEWORK.GetWindowSize().x * 0.5,
		FRAMEWORK.GetWindowSize().y * 0.59);
	ladder->rectangle.setFillColor(sf::Color::Cyan);
	ladder->sortLayer = 1;
}

void SceneGame::Exit()
{
	Scene::Exit();

}

void SceneGame::Update(float dt)
{
	Scene::Update(dt);
	TextGo* findTGo = (TextGo*)FindGo("Info");
	if (SCENE_MGR.TimeBaseFliper())
	{
		findTGo->text.rotate(dt);
	}
	else
	{
		findTGo->text.rotate(-dt);
	}
	

	findTGo = (TextGo*)FindGo("Score");
	PFUnitGo* findPlayer = (PFUnitGo*)FindGo("Player");
	LadderGo* ladder = (LadderGo*)FindGo("Ladder");
	for (int i = 0; i < 9; i++)
	{
		std::string str = "Block" + std::to_string(i);
		BlockGo* findBGo = (BlockGo*)FindGo(str);
		findPlayer->CheckBlock(findBGo);
	}
	findPlayer->CheckLadderBlock(ladder);

	findPlayer->CheckStep();
	findPlayer->CheckBlockSide();
	findPlayer->CheckWallHold();
	findPlayer->CheckLadder();
	if (INPUT_MGR.GetKeyDown(sf::Keyboard::Escape))
	{
		SCENE_MGR.BgmOff();
		SCENE_MGR.ChangeScene(SceneId::Menu);
	}
}

void SceneGame::Draw(sf::RenderWindow& window)
{
	Scene::Draw(window);

}

