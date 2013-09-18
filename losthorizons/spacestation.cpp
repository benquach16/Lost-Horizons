#include "stdafx.h"
#include "spacestation.h"

std::list<SpaceStation*> SpaceStation::allStations;

//constructor
SpaceStation::SpaceStation(const E_GAME_FACTIONS faction, ObjectManager::E_STATION_LIST stationType, const vector3df& position,
						   const vector3df& rotation) : TargetableObject(nextID++, ObjectManager::stationList[stationType], position, rotation,
						   faction), info(stationType), shipSpawnTimer(0)
{
	allStations.push_front(this);
	it = allStations.begin();

	setNormalMap(vdriver->getTexture(ObjectManager::stationList[stationType].getNormalMap().c_str()));
	info.inventory.addItem(ObjectManager::E_ITEM_LIST::IRIDIUM, 100);
}

SpaceStation::~SpaceStation()
{
	allStations.erase(it);
}

void SpaceStation::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
	//do ai stuff here
	//space stations can do several things that are unique to them
	//like spawn ships and create fleets
	if(ObjectManager::stationList[info.stationType].getSpawnShips())
	{
		//spawn ships
		if(shipSpawnTimer < timer->getTime())
		{
			new Ship(getFaction(), ObjectManager::E_SHIP_LIST::PRAE_CRUISER, getPosition(), getRotation());
			shipSpawnTimer = timer->getTime() + ObjectManager::stationList[info.stationType].getShipSpawnTimer();
		}
	}

}

const E_TARGETABLEOBJECT_TYPE SpaceStation::getTargetableObjectType() const
{
	return E_OBJECT_SPACESTATION;
}

const SpaceStationInformation& SpaceStation::getInfo() const
{
	return info;
}

Inventory& SpaceStation::getInventory()
{
	return info.inventory;
}
