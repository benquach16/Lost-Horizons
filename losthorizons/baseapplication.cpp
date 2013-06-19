#include "stdafx.h"
#include "baseapplication.h"
#include <iostream>
#include "config.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

BaseApplication::BaseApplication() : receiver(new KeyListener)
{
	gConfig.Load();

}

BaseApplication::~BaseApplication()
{
	graphics->drop();
	gConfig.Save();
}

void BaseApplication::init()
{
	
	graphics = createDevice(EDT_DIRECT3D9,
		dimension2du(gConfig.iResolutionX, gConfig.iResolutionY),
		gConfig.bBits,
		gConfig.bFullScreen,
		false,
		false,
		receiver);
		
	if(!graphics)
	{
		std::cerr << "Error creating device";
		std::exit(1);
	}
	game = new Gameloop(graphics, receiver);
	graphics->setWindowCaption(L"application");
	
	run();
}

void BaseApplication::run()
{
	//graphics loop
	while(graphics->run())
	{
		graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

		//run game
		game->run();
		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();
	}
}
