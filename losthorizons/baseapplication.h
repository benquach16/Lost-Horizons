#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "irrlicht.h"
#include "gameloop.h"
#include "keylistener.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;




////this is read in from the config
////command line arguments override configuration texts
//struct ConfigArgs
//{
//	bool fullscreen;
//	bool debug;
//	bool shaders;
//	unsigned x, y;
//	unsigned bits;
//
//	bool sound;
//	unsigned volume;
//
//};

class BaseApplication
{
public:
	//default constructor, generate default configs
	BaseApplication();



	~BaseApplication();
	//initialize renderer
	void init();
	//call everything from this function
	void run();

private:
	IrrlichtDevice *graphics;
	KeyListener *receiver;
	Gameloop *game;
};

#endif
