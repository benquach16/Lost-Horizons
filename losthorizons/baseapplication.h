#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "stdafx.h"
#include "irrlicht.h"
#include "startmenu.h"
#include "gameloop.h"
#include "keylistener.h"

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
	//create new device
	void restart();
	//call everything from this function
	void run();

private:
	IrrlichtDevice *graphics;
	KeyListener *receiver;
	StartMenu *menu;
	Gameloop *game;
	HWND hwnd;

	bool menuOpen;

	void buildGraphics();
	void getBits();
	void getPosition();
};

#endif
