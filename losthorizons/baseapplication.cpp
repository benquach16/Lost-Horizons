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
	: menu(0), data(new DataManager), effect(0), then(0), debugStatistics(0)
{
	gConfig.Load();
	getBits();
	receiver = new KeyListener;
	sound = irrklang::createIrrKlangDevice();
	sound->setSoundVolume(gConfig.iSFX/10.f);
	sound->setDefault3DSoundMinDistance(200);
}

BaseApplication::~BaseApplication()
{
	delete receiver;
	delete data;
	sound->drop();
	killDevice();
	gConfig.Save();
}

void BaseApplication::init()
{
	buildGraphics();
	debugStatistics = guienv->getFont("res/font/system.xml");
	menu = new StartMenu(data);
	game = new Gameloop(data);
	console = new DevConsole;
	menu->missionMenuLoad();
	effect = new PostProcessEffect;
	gConfig.bFirstRun = false;
}

void BaseApplication::killDevice()
{
	delete menu;
	delete game;
	delete console;
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

		if (receiver->isKeyPressed(KEY_OEM_3)) {
			console->setVisible(!console->getVisible());
			menu->setVisible(gConfig.bPlay ? false : !menu->getVisible());
		}

		//calculate the new frameDeltaTime
		const u32 now = graphics->getTimer()->getTime();
		frameDeltaTime = (now - then)/1000.f; // Time in seconds
		then = now;

		vdriver->beginScene(true, true, video::SColor(255,0,0,0));

		effect->render();
		//scenemngr->drawAll();
		vdriver->runAllOcclusionQueries(false);
		vdriver->updateAllOcclusionQueries(false);

		//run console, menu, or game
		if (console->getVisible()) {
			console->run();
		} else if (menu->getVisible()) {
			menu->run();
		} else {
			game->run();
			if (receiver->isKeyDown(KEY_ESCAPE)) {
				menu->setVisible(true);
			}
		}

		guienv->drawAll();

		//if (gConfig.bShowFPSCounter)
		debugStatistics->draw(core::stringw(L"fps:") + core::stringw(vdriver->getFPS()), rect<s32>(200,200,0,0), video::SColor(255,0,255,255));

		vdriver->endScene();
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
	if (gConfig.bTopMost && !gConfig.bFullScreen)//get rid of this, no need for it
		SetWindowPos((HWND)vdriver->getExposedVideoData().D3D9.HWnd, HWND_TOPMOST, 0, 0, 0, 0, SWP_NOMOVE | SWP_NOSIZE);
}

void BaseApplication::getBits()
{
	HDC dc = GetDC(NULL);
	gConfig.iBits = GetDeviceCaps(dc, BITSPIXEL);
	ReleaseDC(NULL, dc);
}
