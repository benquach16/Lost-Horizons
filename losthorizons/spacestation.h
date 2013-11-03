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
	static std::vector<SpaceStation*> allStations;

	SpaceStation(const E_GAME_FACTION faction, const ObjectManager::E_STATION_LIST stationType, const vector3df &position,
		const vector3df &rotation);
	virtual ~SpaceStation();
	virtual bool run();

	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	const SpaceStationInformation& getInfo() const;
	Inventory& getInventory();

protected:
	SpaceStationInformation info;

private:
	//timer 
	u32 shipSpawnTimer;

	//iterator to this
	unsigned index;
};

#endif
