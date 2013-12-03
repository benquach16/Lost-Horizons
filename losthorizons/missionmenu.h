#ifndef _MISSIONMENU_H_
#define _MISSIONMENU_H_

#include "menuwindow.h"

using namespace irr;

class MissionMenu : public MenuWindow
{
 public:
	MissionMenu(gui::IGUIWindow *menu);
	~MissionMenu();

	void run();
 protected:
	//do menustuff
	gui::IGUIListBox *missionList;
	gui::IGUIButton *accept;
	gui::IGUIButton *cancel;
};

#endif
 
