#ifndef _MISSIONPROPERTIES_H_
#define _MISSIONPROPERTIES_H_

#include <string>
#include <queue>
#include "objective.h"

//we use this because we dont want to create the ships
//when this file is parsed. instead, we want to 
//create them when the mission is assigned to the player
struct shipCreateQueue
{
	ObjectManager::E_SHIP_LIST shipType;
	E_GAME_FACTION faction;
	vector3df position, rotation;
	shipCreateQueue(ObjectManager::E_SHIP_LIST shipType, E_GAME_FACTION faction,
									vector3df &position, vector3df &rotation) : shipType(shipType),
									faction(faction), position(position), rotation(rotation) {}
	
};
//for story missions or for cool missions we create
//not randomly generated
class MissionProperties
{
public:
	MissionProperties(const std::string& f);
	~MissionProperties();

	const wchar_t *getName() const;
	const wchar_t *getDesc() const;
	const std::vector<Objective>& getObjs() const;
	std::queue<shipCreateQueue> getCreationQueue() const;
protected:
	E_OBJECTIVE_TYPE getObjectiveType(const wchar_t *text);
	std::wstring name;
	std::wstring description;
	unsigned numOfObjectives;
	std::vector<Objective> objectives;
	std::queue<shipCreateQueue> creationQueue;
};

#endif
