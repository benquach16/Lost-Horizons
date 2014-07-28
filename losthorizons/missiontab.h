#ifndef _MISSIONTAB_H_
#define _MISSIONTAB_H_

#include "menutab.h"
#include "missionmanager.h"
#include "marker.h"

class MissionTab : public MenuTab
{
public:
	MissionTab(IGUITabControl *tabs);
	~MissionTab();

	void run();

private:
	void loadMissions();
	//list of all the missions
	IGUIListBox *missionList;
	IGUIStaticText *missionDescription;
	IGUIListBox *objectivesList;
	MissionManager *missionManager;
	Marker *marker;
};

#endif
