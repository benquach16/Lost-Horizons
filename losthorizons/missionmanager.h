#ifndef _MISSIONMANAGER_H_
#define _MISSIONMANAGER_H_

#include <vector>

#include "mission.h"
#include "intercom.h"

//missionmanager class
//manages missions
class MissionManager
{
public:
	MissionManager();
	~MissionManager();

	//run function
	void run(Intercom *intercom);

	void addMission(const MissionProperties& missionInfo);

	//returns an rvalue
	const std::vector<Mission*>& getMissions() const;

protected:
	std::vector<Mission*> missionList;
};

#endif
