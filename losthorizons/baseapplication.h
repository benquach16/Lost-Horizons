#ifndef _BASEAPPLICATION_H_
#define _BASEAPPLICATION_H_

//run all the main loops from the base point

#include "devconsole.h"
#include "datamanager.h"
#include "postprocess.h"
#include "startmenu.h"
#include "missionmenu.h"

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
	StartMenu *menu;
	DataManager *data;
	PostProcessEffect *effect;

	void buildGraphics();
	void getBits();

	//for delta time calculation
	u32 then;
};

#endif
