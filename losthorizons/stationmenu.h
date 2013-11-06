#ifndef _STATIONMENU_H_
#define _STATIONMENU_H_

#include "menuwindow.h"
#include "storetab.h"
#include "hangartab.h"
#include "jobtab.h"

//ui menu that is opened when the player is docked at a space staiton
class StationMenu : public MenuWindow
{
public:
	StationMenu(Ship *player);
	~StationMenu();
	virtual void run(const TargetableObject *target);
	
protected:
	gui::IGUITabControl *tabs;
	StoreTab *store;
	HangarTab *hangar;
	JobTab *job;
};

#endif
