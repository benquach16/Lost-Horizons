#ifndef _MENUTAB_H_
#define _MENUTAB_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;

//abstract bass class for menu tabs
class MenuTab
{
public:
	MenuTab() : tab(0)
	{
	}
	~MenuTab()
	{
	}
	//pure virtual function
	virtual void run() = 0;

protected:
	gui::IGUITab *tab;
};

#endif
