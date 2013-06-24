#include "stdafx.h"
#include "baseapplication.h"
#include "config.h"
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
	delete menu;
	delete game;
	delete receiver;
	graphics->closeDevice();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();
	menu = new StartMenu(graphics);
	game = new Gameloop(graphics, receiver);
	gConfig.bFirstRun = false;
}

void BaseApplication::restart()
{
	delete menu;
	delete game;
	getPosition();
	graphics->drop();
	SetParent(hwnd, HWND_MESSAGE);
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
			if (!menu->run()) {
				bool quit = true;
				if (gConfig.bConfirmOnQuit)
					if (IDNO == MessageBox(hwnd, L"Are you sure you want to exit?", L"Are you sure?", MB_YESNO | MB_ICONQUESTION))
						quit = false;
				if (quit) {
					graphics->getVideoDriver()->endScene();
					getPosition();
					return;
				}
			}
		} else {
			if (!game->run()) {
				menuOpen = true;
			}
		}

		if (gConfig.bRestart) {
			gConfig.bRestart = false;
			restart();
		}

		graphics->getSceneManager()->drawAll();
		graphics->getGUIEnvironment()->drawAll();

		graphics->getVideoDriver()->endScene();
	}
}

void BaseApplication::buildGraphics()
{
	graphics = createDevice(EDT_DIRECT3D9,
		dimension2d<u32>(gConfig.iResolutionX, gConfig.iResolutionY),
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
	if (gConfig.bFullScreen) {
		//don't change anything
	} else if (gConfig.bTopMost) {
		SetWindowPos(hwnd, HWND_TOPMOST, gConfig.iWindowX, gConfig.iWindowY, 0, 0, SWP_NOSIZE);
	} else {
		SetWindowPos(hwnd, HWND_TOP, gConfig.iWindowX, gConfig.iWindowY, 0, 0, SWP_NOSIZE);
	}
}

void BaseApplication::getBits()
{
	HDC dc = GetDC(NULL);
	gConfig.iBits = GetDeviceCaps(dc, BITSPIXEL);
	ReleaseDC(NULL, dc);
}

void BaseApplication::getPosition()
{
	WINDOWPLACEMENT placement;
	GetWindowPlacement(hwnd, &placement);
	if (placement.showCmd == SW_SHOWNORMAL) {
		RECT rc;
		GetWindowRect(hwnd, &rc);
		gConfig.iWindowX = rc.left;
		gConfig.iWindowY = rc.top;
	}
}
