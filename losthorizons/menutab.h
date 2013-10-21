#ifndef _MENUTAB_H_
#define _MENUTAB_H_

#include "stdafx.h"

using namespace irr;
using namespace gui;

//abstract bass class for menu tabs
class MenuTab
{
public:
	MenuTab() : tab(0) {}
	~MenuTab() {}
	//pure virtual function
	void run();

protected:
	IGUITab *tab;
};

#endif
