#include "stdafx.h"
#include "baseapplication.h"
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

	graphics->setWindowCaption(L"application");
	
	run();
}

void BaseApplication::run()
{
	//graphics loop
	while(graphics->run())
	{
		graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();
	}
}
