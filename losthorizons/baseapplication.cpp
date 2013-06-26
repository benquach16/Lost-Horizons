#include "stdafx.h"
#include "baseapplication.h"
#include <iostream>
#include <SExposedVideoData.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

BaseApplication::BaseApplication()
	: graphics(0), receiver(new KeyListener), menu(0), game(0), hwnd(0), menuOpen(true)
{
	getBits();
	gConfig.Load();
}

BaseApplication::~BaseApplication()
{
	delete receiver;
	killDevice();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();
	menu = new StartMenu(graphics);
	game = new Gameloop(graphics, receiver);
	gConfig.bFirstRun = false;
}

void BaseApplication::killDevice()
{
	delete menu;
	delete game;
	graphics->getVideoDriver()->removeAllTextures();
	graphics->closeDevice();
	graphics->run();
    graphics->drop();
}

void BaseApplication::restartDevice()
{
	killDevice();
	init();
	graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));
	menu->run();
}

void BaseApplication::run()
{
	//graphics loop
	while (graphics->run())
	{
		graphics->getVideoDriver()->beginScene(true, true, SColor(255,100,101,140));

		//run menu or game
		if (menuOpen) {
			menu->setVisible(true);
			menuOpen = menu->run();
			if (!menuOpen && !gConfig.bPlay) {
				if (gConfig.bConfirmOnQuit)
					if (IDNO == MessageBox(hwnd, L"Are you sure you want to exit?", L"Are you sure?", MB_YESNO | MB_ICONQUESTION))
						menuOpen = true;
				if (!menuOpen) {
					graphics->getVideoDriver()->endScene();
					return;
				}
			}
		} else {
			menu->setVisible(false);
			menu->run();
			menuOpen = !game->run();
		}

		if (gConfig.bRestart) {
			gConfig.bRestart = false;
			restartDevice();
		}
		
		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();
	}
}

void BaseApplication::buildGraphics()
{
	if (gConfig.bFullScreen)
		graphics = createDevice(EDT_DIRECT3D9,
			dimension2d<u32>(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)),
			gConfig.iBits,
			gConfig.bFullScreen,
			false,
			gConfig.bVsync,
			receiver);
	else
		graphics = createDevice(EDT_DIRECT3D9,
			dimension2d<u32>(gConfig.iResolutionX, gConfig.iResolutionY),
			gConfig.iBits,
			gConfig.bFullScreen,
			false,
			gConfig.bVsync,
			receiver);
		
	if(!graphics)
	{
		std::exit(1);
	}
	
	graphics->setWindowCaption(L"Lost Horizons");
	SExposedVideoData InternalData = graphics->getVideoDriver()->getExposedVideoData();;
	switch(EDT_DIRECT3D9) { //use variable if we ever implement using the other drivers
            case EDT_OPENGL:
				hwnd  = (HWND) InternalData.OpenGLWin32.HWnd;
                break;
            case EDT_DIRECT3D8:
                hwnd  = (HWND) InternalData.D3D8.HWnd;
                break;
            case EDT_DIRECT3D9:
                hwnd  = (HWND) InternalData.D3D9.HWnd;
                break;
	}
	if (gConfig.bTopMost && !gConfig.bFullScreen)
		SetWindowPos(hwnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void BaseApplication::getBits()
{
	HDC dc = GetDC(NULL);
	gConfig.iBits = GetDeviceCaps(dc, BITSPIXEL);
	ReleaseDC(NULL, dc);
}

