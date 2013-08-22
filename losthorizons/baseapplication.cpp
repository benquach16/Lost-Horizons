#include "stdafx.h"
#include "baseapplication.h"
#include <iostream>
#include <SExposedVideoData.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrklang.lib")
#endif

BaseApplication::BaseApplication()
	: graphics(0), receiver(new KeyListener), data(new DataManager), menu(0), effect(0), hwnd(0), then((f32)(0))
{
	getBits();
	gConfig.Load();
}

BaseApplication::~BaseApplication()
{
	delete receiver;
	delete data;
	killDevice();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();
	menu = new StartMenu(graphics, receiver, data);
	game = new Gameloop(graphics, receiver, data);
	effect = new PostProcessEffect;
	gConfig.bFirstRun = false;
}

void BaseApplication::killDevice()
{
	delete menu;
	delete game;
	delete effect;
	graphics->closeDevice();
	graphics->run();
    graphics->drop();
	sound->drop();
}

void BaseApplication::run()
{
	//graphics loop
	while (graphics->run())
	{
		if (gConfig.bExit) {
			return;
		}
		if (gConfig.bRestart) {
			gConfig.bRestart = false;
			data->pull();
			killDevice();
			init();
			if (gConfig.bPlay)
				menu->shift();
			data->push();
		}

		vdriver->beginScene(true, true, SColor(255,0,0,0));

		//run menu or game
		const f32 now = (f32)(graphics->getTimer()->getTime());
		const f32 frameDeltaTime = (now-then)/1000.f; // Time in seconds
		then = now;
		menu->run();
		effect->render();
		if (!menu->getVisible()) {
			game->run(frameDeltaTime);
			if (receiver->isKeyDown(irr::KEY_ESCAPE))
				menu->setVisible(true);
		}
		guienv->drawAll();

		vdriver->endScene();
	}
}

void BaseApplication::buildGraphics()
{
	sound = irrklang::createIrrKlangDevice();
	sound->setSoundVolume(1.0f);
	sound->setDefault3DSoundMinDistance(1000);
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
		
	if (!graphics)
		std::exit(1);

	vdriver = graphics->getVideoDriver();
	scenemngr = graphics->getSceneManager();
	guienv = graphics->getGUIEnvironment();
	timer = graphics->getTimer();
	soundmngr = sound;
	gConfig.screen = vdriver->getScreenSize();
	
	graphics->setWindowCaption(L"Lost Horizons");
	SExposedVideoData InternalData = vdriver->getExposedVideoData();
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
