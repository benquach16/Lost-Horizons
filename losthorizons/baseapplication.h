#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "irrlicht.h"
#include "startmenu.h"
#include "keylistener.h"
#include "datamanager.h"

using namespace irr;
using namespace core;
using namespace video;

class BaseApplication
{
public:
	//default constructor, generate default configs
	BaseApplication();
	~BaseApplication();
	//initialize renderer
	void init();
	//destroy the device cleanly
	void killDevice();
	//call everything from this function
	void run();

private:
	IrrlichtDevice *graphics;
	KeyListener *receiver;
	DataManager *data;
	StartMenu *menu;
	HWND hwnd;

	void buildGraphics();
	void getBits();
};

#endif
