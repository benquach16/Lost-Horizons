#ifndef _MISSION_H_
#define _MISSION_H_

#include <vector>

#include "objective.h"
#include "missionproperties.h"


//mission class
class Mission
{
public:
	Mission();
	//paramaterized constructor
	Mission(bool generateMission);
	Mission(const MissionProperties& missionInfo);
	~Mission();

protected:
	std::wstring name;
	std::wstring description;
	std::vector<Objective> objectives;

};

#endif
