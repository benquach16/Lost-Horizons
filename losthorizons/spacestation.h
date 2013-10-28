#ifndef _SPACESTATION_H_
#define _SPACESTATION_H_

#include "targetableobject.h"
#include "objectmanager.h"
#include "inventory.h"

struct SpaceStationInformation
{
	ObjectManager::E_STATION_LIST stationType;
	Inventory inventory;
	SpaceStationInformation() {}
	SpaceStationInformation(ObjectManager::E_STATION_LIST stationType) : stationType(stationType)
	{}
};

//spacestation class
class SpaceStation : public TargetableObject
{
public:
	static std::list<SpaceStation*> allStations;

	SpaceStation(const E_GAME_FACTION faction, ObjectManager::E_STATION_LIST stationType, const vector3df &position,
		const vector3df &rotation);
	virtual ~SpaceStation();
	virtual void run(f32 frameDeltaTime);

	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	const SpaceStationInformation& getInfo() const;
	Inventory& getInventory();
protected:
	//iterator to this
	std::list<SpaceStation*>::iterator it;

	SpaceStationInformation info;

	//timer 
	u32 shipSpawnTimer;
};

#endif
