#include "stdafx.h"
#include "baseapplication.h"
#include "globals.h"
#include "config.h"
#include <iostream>
#include <SExposedVideoData.h>

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#pragma comment(lib, "irrklang.lib")
#endif

using namespace base;

BaseApplication::BaseApplication()
	: menu(0), data(new DataManager), effect(0), then(0.f)
{
	gConfig.Load();
	getBits();
	receiver = new KeyListener;
	sound = irrklang::createIrrKlangDevice();
	sound->setSoundVolume(gConfig.iSFX/10.f);
	sound->setDefault3DSoundMinDistance(200);
	console = new DevConsole;
}

BaseApplication::~BaseApplication()
{
	delete receiver;
	delete data;
	sound->drop();
	delete console;
	killDevice();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();

	menu = new StartMenu(data);
	game = new Gameloop(data);
	menu->missionMenuLoad();
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
}

void BaseApplication::run()
{
	//graphics loop
	while (gConfig.bRun && graphics->run())
	{
		if (gConfig.bRestart) {
			gConfig.bRestart = false;
			data->pull();
			killDevice();
			init();
			if (gConfig.bPlay)
				menu->shift();
			data->push();
		}

		vdriver->beginScene(true, true, video::SColor(255,0,0,0));

		//calculate the new frameDeltaTime
		const f32 now = (f32)graphics->getTimer()->getTime();
		frameDeltaTime = (now - then)/1000.f; // Time in seconds
		then = now;

		//run menu or game
		menu->run();

		effect->render();
		//scenemngr->drawAll();
		vdriver->runAllOcclusionQueries(false);
		vdriver->updateAllOcclusionQueries(false);
		if (!menu->getVisible()) {
			game->run();
			if (receiver->isKeyDown(KEY_ESCAPE)) {
				menu->setVisible(true);
			}
		}

		guienv->drawAll();

		vdriver->endScene();

		if (receiver->isKeyPressed(KEY_OEM_3)) {
			SetForegroundWindow(GetConsoleWindow());
			console->run();
			SetForegroundWindow((HWND)vdriver->getExposedVideoData().D3D9.HWnd);
		}
	}
}

void BaseApplication::buildGraphics()
{
	//initialize graphics engine
	if (gConfig.bFullScreen)
		graphics = createDevice(video::EDT_DIRECT3D9,
			dimension2d<u32>(GetSystemMetrics(SM_CXSCREEN), GetSystemMetrics(SM_CYSCREEN)),
			gConfig.iBits,
			gConfig.bFullScreen,
			false,
			gConfig.bVsync,
			receiver);
	else
		graphics = createDevice(video::EDT_DIRECT3D9,
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
	width = vdriver->getScreenSize().Width;
	height = vdriver->getScreenSize().Height;
	
	graphics->setWindowCaption(L"Lost Horizons");
	if (gConfig.bTopMost && !gConfig.bFullScreen)
		SetWindowPos((HWND)vdriver->getExposedVideoData().D3D9.HWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void BaseApplication::getBits()
{
	HDC dc = GetDC(NULL);
	gConfig.iBits = GetDeviceCaps(dc, BITSPIXEL);
	ReleaseDC(NULL, dc);
}
