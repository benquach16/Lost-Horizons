#include "spacestation.h"

std::list<SpaceStation*> SpaceStation::allStations;

SpaceStation::SpaceStation(const E_GAME_FACTIONS faction, ObjectManager::E_STATION_LIST stationType, const vector3df& position,
						   const vector3df& rotation) : TargetableObject(nextID++, ObjectManager::stationList[stationType], position, rotation,
						   faction)
{
	allStations.push_front(this);
	it = allStations.begin();
}

SpaceStation::~SpaceStation()
{
	allStations.erase(it);
}

void SpaceStation::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
}
