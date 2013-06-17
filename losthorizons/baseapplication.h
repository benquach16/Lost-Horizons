#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "irrlicht.h"


using namespace irr;
using namespace core;
using namespace scene;
using namespace video;
using namespace gui;

struct CommandLineArgs
{
	bool fullscreen;
	bool debug;
	unsigned x, y;
};

class CBaseApplication
{
public:
	//default constructor, generate default configs
	CBaseApplication();
	//parameterized constructor
	CBaseApplication(ConfigArgs &config_args);
	CBaseApplication(ConfigArgs &config_args, CommandLineArgs &args);
	//call everything from this function
	void run();

private:
	IrrlichtDevice *graphics;
};

#endif
