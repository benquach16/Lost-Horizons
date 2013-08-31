#include "stdafx.h"
#include "spacestation.h"

std::list<SpaceStation*> SpaceStation::allStations;

SpaceStation::SpaceStation(const E_GAME_FACTIONS faction, ObjectManager::E_STATION_LIST stationType, const vector3df& position,
						   const vector3df& rotation) : TargetableObject(nextID++, ObjectManager::stationList[stationType], position, rotation,
						   faction)
{
	allStations.push_front(this);
	it = allStations.begin();

	setNormalMap(vdriver->getTexture(ObjectManager::stationList[stationType].getNormalMap().c_str()));
}

SpaceStation::~SpaceStation()
{
	allStations.erase(it);
}

void SpaceStation::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
	//do ai stuff here
	
}

const E_TARGETABLEOBJECT_TYPE SpaceStation::getTargetableObjectType() const
{
	return E_OBJECT_SPACESTATION;
}
