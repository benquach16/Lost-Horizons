#ifndef _MISSIONMENU_H_
#define _MISSIONMENU_H_

#include "irrlicht.h"
#include "menuwindow.h"
#include "missionproperties.h"

using namespace irr;

class MissionMenu : public MenuWindow
{
 public:
	MissionMenu();
	~MissionMenu();
	void getMissionList();
	void run();
 protected:
	//do menustuff

	gui::IGUIListBox *missionList;
	gui::IGUIStaticText *description;
	gui::IGUIButton *accept;
	gui::IGUIButton *cancel;
};

#endif
 
