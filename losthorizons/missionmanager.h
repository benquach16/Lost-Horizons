#ifndef _MISSIONMANAGER_H_
#define _MISSIONMANAGER_H_

#include <vector>

#include "mission.h"

//missionmanager class
//manages missions
class MissionManager
{
public:
	MissionManager();
	~MissionManager();
protected:
	std::vector<Mission> data;
};

#endif
