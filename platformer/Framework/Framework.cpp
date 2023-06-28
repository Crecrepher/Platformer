#include "stdafx.h"
#include "Framework.h"
#include "InputMgr.h"
#include "SceneMgr.h"
#include "ResourceMgr.h"

Framework::Framework(int w, int h, const std::string& t)
    :screenWidth(w), screenHeight(h), title(t)
{
}

void Framework::Init(int width, int height, const std::string& title)
{
	window.create(sf::VideoMode(width, height), title);
    //ÀüÃ¼¾µ°Å ±×¸®±â
    RESOURCE_MGR.Load(ResourceTypes::Font, "fonts/DS-DIGI.ttf");
    RESOURCE_MGR.Load(ResourceTypes::Texture, "graphics/player4.png");
    //ÆÀ¹ö²¨
    RESOURCE_MGR.Load(ResourceTypes::Font, "fonts/KOMIKAP_.ttf");
    RESOURCE_MGR.Load(ResourceTypes::Texture, "graphics/timber_icon.png");
    RESOURCE_MGR.Load(ResourceTypes::Texture, "graphics/title.png");
    RESOURCE_MGR.Load(ResourceTypes::Sound, "sound/chop.wav");
    RESOURCE_MGR.Load(ResourceTypes::Sound, "sound/death.wav");
    RESOURCE_MGR.Load(ResourceTypes::Sound, "sound/bgm_main.wav");
    SCENE_MGR.Init();

 
}

void Framework::Release()
{
    RESOURCE_MGR.UnLoad(ResourceTypes::Texture, "graphics/player4.png");
    RESOURCE_MGR.UnLoad(ResourceTypes::Font, "fonts/KOMIKAP_.ttf");
    RESOURCE_MGR.UnLoad(ResourceTypes::Texture, "graphics/title.png");
    RESOURCE_MGR.UnLoad(ResourceTypes::Texture, "graphics/timber_icon.png");
    RESOURCE_MGR.UnLoad(ResourceTypes::Sound, "sound/chop.wav");
    RESOURCE_MGR.UnLoad(ResourceTypes::Sound, "sound/death.wav");
    RESOURCE_MGR.UnLoad(ResourceTypes::Sound, "sound/bgm_main.wav");
    SCENE_MGR.Release();
}

void Framework::Update(float dt)
{

    SCENE_MGR.Update(dt);
}

void Framework::Draw()
{
    SCENE_MGR.Draw(window);
}

void Framework::Run()
{
    Init(screenWidth, screenHeight,title);

    clock.restart();
    while (window.isOpen())
    {
        sf::Time deltaTime = clock.restart();
        float dt = deltaTime.asSeconds();

        INPUT_MGR.Clear();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();

            INPUT_MGR.Update(event);
        }

        Update(dt);
        window.clear();
        //window.draw(shape);
        Draw();
        window.display();
    }
    Release();
}

sf::Vector2f Framework::GetWindowSize()
{
    return sf::Vector2f(screenWidth, screenHeight);
}
