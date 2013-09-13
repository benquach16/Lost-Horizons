#ifndef _MISSION_H_
#define _MISSION_H_

#include <vector>

#include "objective.h"


//mission class
class Mission
{
public:
	Mission();
	//paramaterized constructor
	Mission(bool generateMission);
	~Mission();

protected:
	std::vector<Objective> objectives;

};

#endif
