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
	receiver = new KeyListener;
	sound = irrklang::createIrrKlangDevice();
	sound->setSoundVolume(1.0f);
	sound->setDefault3DSoundMinDistance(500);
	getBits();
	gConfig.Load();
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
	menu = new StartMenu(data);
	game = new Gameloop(data);
	//effect = new PostProcessEffect;
	gConfig.bFirstRun = false;
}

void BaseApplication::killDevice()
{
	delete menu;
	delete game;
	//delete effect;
	graphics->closeDevice();
	graphics->run();
    graphics->drop();
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

		vdriver->beginScene(true, true, video::SColor(255,0,0,0));

		//run menu or game
		const f32 now = (f32)(graphics->getTimer()->getTime());
		const f32 frameDeltaTime = (now - then)/1000.f; // Time in seconds
		then = now;
		menu->run();
		//effect->render();
		scenemngr->drawAll();
		vdriver->runAllOcclusionQueries(false);
		vdriver->updateAllOcclusionQueries(false);
		if (!menu->getVisible()) {
			game->run(frameDeltaTime);
			if (receiver->isKeyDown(irr::KEY_ESCAPE))
			{
				menu->setVisible(true);
			}
		}

		guienv->drawAll();

		vdriver->endScene();
	}
}

void BaseApplication::buildGraphics()
{
	//initialize graphics engnie
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
