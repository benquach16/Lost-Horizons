#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "irrlicht.h"
#include "gameloop.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;


class CBaseApplication
{
public:
	//default constructor, generate default configs
	CBaseApplication();

	~CBaseApplication();
	//initialize renderer
	void init();
	//call everything from this function
	void run();

private:
	IrrlichtDevice *graphics;

	CGameloop *game;
};

#endif
