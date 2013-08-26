#ifndef _SPACESTATION_H_
#define _SPACESTATION_H_

#include <list>

#include "targetableobject.h"
#include "objectmanager.h"

//spacestation class
class SpaceStation : public TargetableObject
{
public:
	static std::list<SpaceStation*> allStations;

	SpaceStation(const E_GAME_FACTIONS faction, ObjectManager::E_STATION_LIST stationType, const vector3df &position,
		const vector3df &rotation);
	virtual ~SpaceStation();
	virtual void run(f32 frameDeltaTime);

protected:
	//iterator to this
	std::list<SpaceStation*>::iterator it;
};

#endif
