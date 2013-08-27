#ifndef _STATIONMENU_H_
#define _STATIONMENU_H_

#include "spacestation.h"
#include "menuwindow.h"

class StationMenu : public MenuWindow
{
public:
	StationMenu();
	virtual ~StationMenu();
	void run(const TargetableObject *target);
	
protected:
	gui::IGUITabControl *tabs;

};

#endif
