#include "stdafx.h"
#include "baseapplication.h"

#define DEFAULT_X 1024
#define DEFAULT_Y 768

#ifdef _IRR_WINDOWS_
#pragma comment(lib, "Irrlicht.lib")
#endif

CBaseApplication::CBaseApplication()
{
	//set default values
	config_args.fullscreen = true;
	config_args.x = DEFAULT_X;
	config_args.y = DEFAULT_Y;
}

CBaseApplication::CBaseApplication(ConfigArgs &config_args) : config_args(config_args)
{
}

CBaseApplication::CBaseApplication(ConfigArgs &config_args, CommandLineArgs &args) : config_args(config_args),
	args(args)
{
}

CBaseApplication::~CBaseApplication()
{
	graphics->drop();
}

void CBaseApplication::init()
{
	graphics = createDevice(EDT_DIRECT3D9,
		dimension2du(config_args.x, config_args.y),
		config_args.bits,
		config_args.fullscreen,
		false,
		false,
		0);

	graphics->setWindowCaption(L"application");

	run();
}

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