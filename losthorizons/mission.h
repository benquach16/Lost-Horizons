#ifndef _MISSION_H_
#define _MISSION_H_


enum E_MISSION_TYPES
{
	E_MISSIONTYPE_SWEEP,
	E_MISSIONTYPE_COURIER,
	E_MISSIONTYPE_NAVIGATE,
	E_MISSIONTYPE_RETREVIAL,
	E_MISSIONTYPE_DEFEND
};

//mission class
class Mission
{
public:
	Mission();
	//paramaterized constructor
	Mission(bool generateMission);
	~Mission();
};

#endif
