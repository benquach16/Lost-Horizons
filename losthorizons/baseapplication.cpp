#include "stdafx.h"
#include "baseapplication.h"
#include "config.h"

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

CBaseApplication::CBaseApplication()
{
	// defaults set automatically during ini loading
	gConfig.Load();
}

CBaseApplication::~CBaseApplication()
{
	graphics->drop();
	gConfig.Save();
}

//void CBaseApplication::init()
//{
//	graphics = createDevice(EDT_DIRECT3D9,
//		dimension2du(gConfig.iResolutionX, gConfig.iResolutionY),
//		config_args.bits, // what is this for? we'll add it to the Config struct if it's needed
//		config_args.fullscreen, // redundant stuff is bad, we'll talk about this later
//		false,
//		false,
//		0);
//
//	graphics->setWindowCaption(L"application");
//
//	run();
//}

void CBaseApplication::run()
{

	while(graphics->run())
	{
		graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();
	}
}
