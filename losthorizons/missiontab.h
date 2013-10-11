#ifndef _MISSIONTAB_H_
#define _MISSIONTAB_H_

#include "menutab.h"

class MissionTab : public MenuTab
{
public:
	MissionTab(gui::IGUITabControl *tabs);
	~MissionTab();

protected:
	//list of all the missions
	gui::IGUIListBox *missionList;
	gui::IGUIStaticText *missionDescription;

};

#endif
