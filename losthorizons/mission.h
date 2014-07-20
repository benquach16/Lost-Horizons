#ifndef _MISSION_H_
#define _MISSION_H_

#include <vector>

#include "objective.h"
#include "missionproperties.h"

//mission class
class Mission
{
public:
	//default constructor is for random mission generation
	Mission();
	//paramaterized constructor
	Mission(const MissionProperties& missionInfo);
	~Mission();

	bool run();
	
	const wchar_t *getName() const;
	const wchar_t *getDesc() const;

	const vector3df getCurrObjPos() const;

protected:
	std::wstring name;
	std::wstring description;
	std::vector<Objective*> objectives;

};

#endif
