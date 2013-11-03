#include "stdafx.h"
#include "spacestation.h"
#include "globals.h"
#include <iostream>

using namespace base;

std::vector<SpaceStation*> SpaceStation::allStations;

//constructor
SpaceStation::SpaceStation(const E_GAME_FACTION faction, const ObjectManager::E_STATION_LIST stationType, const vector3df& position, const vector3df& rotation)
	: TargetableObject(nextID++, *ObjectManager::stationList[stationType], position, rotation, faction), info(stationType),
	  shipSpawnTimer(0), index(allStations.size())
{
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]SpaceStation object created" << std::endl;

	allStations.push_back(this);

	setNormalMap(vdriver->getTexture(ObjectManager::stationList[stationType]->getNormalMap()));
	info.inventory.addItem(ObjectManager::E_ITEM_LIST::IRIDIUM, 100);
}

SpaceStation::~SpaceStation()
{
	allStations[index] = allStations.back();
	allStations[index]->index = index;
	allStations.pop_back();
}

bool SpaceStation::run()
{
	//do ai stuff here
	//space stations can do several things that are unique to them
	//like spawn ships and create fleets
	if (ObjectManager::stationList[info.stationType]->getSpawnShips())
	{
		//spawn ships
		if (shipSpawnTimer < timer->getTime())
		{
			new Ship(getFaction(), ObjectManager::E_SHIP_LIST::PRAE_CRUISER, getPosition(), getRotation());
			shipSpawnTimer = timer->getTime() + ObjectManager::stationList[info.stationType]->getShipSpawnTimer();
		}
	}
	return TargetableObject::run();
}

const E_TARGETABLEOBJECT_TYPE SpaceStation::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_SPACESTATION;
}

const SpaceStationInformation& SpaceStation::getInfo() const
{
	return info;
}

Inventory& SpaceStation::getInventory()
{
	return info.inventory;
}
