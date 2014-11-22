#ifndef _MISSIONMENU_H_
#define _MISSIONMENU_H_

#include "irrlicht.h"
#include "menuwindow.h"

using namespace irr;

class MissionMenu : public MenuWindow
{
 public:
	MissionMenu(gui::IGUIWindow *menu);
	~MissionMenu();
	void run();
	void loadMissions();
	void clear();
 protected:
	//do menustuff

	gui::IGUIListBox *missionList;
	gui::IGUIStaticText *description;
	gui::IGUIButton *accept;
	gui::IGUIButton *cancel;
};

#endif
 