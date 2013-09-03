#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <list>

#include "targetableobject.h"
#include "fighterproperties.h"
#include "objectmanager.h"

//fighter class
//they mostly provide something for point defense to kill
class Fighter : public TargetableObject
{
public:
	static std::list<Fighter*> allFighters;

	Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTIONS faction, u32 homeBaseID);
	virtual ~Fighter();
	virtual void run(f32 frameDeltaTime);
protected:

	std::list<Fighter*>::iterator it;

	u32 homeBaseID;
	int maxHull, hull;
	int maxVelocity, velocity;
	int maxTurn;
	unsigned maxFuel, fuel;
};

#endif
