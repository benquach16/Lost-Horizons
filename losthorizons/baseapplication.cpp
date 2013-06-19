#include "stdafx.h"
#include "baseapplication.h"
#include "config.h"
#include <iostream>
//#include <SExposedVideoData.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

BaseApplication::BaseApplication() : graphics(0), receiver(new KeyListener), game(0)
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
	buildGraphics();
	game = new Gameloop(graphics, receiver);
	run();
}

void BaseApplication::restart()
{
	IrrlichtDevice *oldGraphics = graphics;
	buildGraphics();
	oldGraphics->drop();
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

		if (resolutionX != gConfig.iResolutionX ||
			resolutionY != gConfig.iResolutionY ||
			fullScreen != gConfig.bFullScreen ||
			vSync != gConfig.bVsync) {
			restart();
		}
	}
}

void BaseApplication::buildGraphics()
{
	graphics = createDevice(EDT_DIRECT3D9,
		dimension2du(gConfig.iResolutionX, gConfig.iResolutionY),
		gConfig.iBits,
		gConfig.bFullScreen,
		false,
		gConfig.bVsync,
		receiver);
		
	if(!graphics)
	{
		std::cerr << "Error creating device";
		std::exit(1);
	}

	//SExposedVideoData InternalData = graphics->getVideoDriver()->getExposedVideoData();;
	//switch(EDT_DIRECT3D9) { //use variable if we ever implement using the other drivers
 //           case EDT_OPENGL:
	//			hwnd  = (HWND) InternalData.OpenGLWin32.HWnd;
 //               break;

 //           case EDT_DIRECT3D8:
 //               hwnd  = (HWND) InternalData.D3D8.HWnd;
 //               break;

 //           case EDT_DIRECT3D9:
 //               hwnd  = (HWND) InternalData.D3D9.HWnd; std::cerr << hwnd << " is the handle?" << std::endl;
 //               break;
	//}
	//if (MoveWindow(hwnd, gConfig.iWindowX, gConfig.iWindowY, gConfig.iResolutionX, gConfig.iResolutionY, true)) {
	//	std::cerr << "moved it like a boss" << std::endl;
	//} else {
	//	std::cerr << "no cheese" << std::endl;
	//} ///////////////////////////////////////////////////////////doesn't work (sad face)
	
	resolutionX = gConfig.iResolutionX;
	resolutionY = gConfig.iResolutionY;
	fullScreen = gConfig.bFullScreen;
	vSync = gConfig.bVsync;
}
