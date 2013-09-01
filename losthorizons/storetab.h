#ifndef _STORETAB_H_
#define _STORETAB_H_

#include "irrlicht.h"
#include "menutab.h"

using namespace irr;
using namespace core;
using namespace gui;

//create a class for each tab
//this class is meant for use by the stationmenu class
class StoreTab : public MenuTab
{
public:
	StoreTab(gui::IGUITabControl *tabs);
	~StoreTab();
	virtual void run();
protected:

};

#endif
