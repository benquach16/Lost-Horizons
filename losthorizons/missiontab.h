#ifndef _MISSIONTAB_H_
#define _MISSIONTAB_H_

#include "menutab.h"
#include "missionmanager.h"

class MissionTab : public MenuTab
{
public:
	MissionTab(gui::IGUITabControl *tabs, MissionManager *missionManager);
	~MissionTab();

	void run();

protected:
	void loadMissions();
	//list of all the missions
	gui::IGUIListBox *missionList;
	gui::IGUIStaticText *missionDescription;

	MissionManager *missionManager;

};

#endif
