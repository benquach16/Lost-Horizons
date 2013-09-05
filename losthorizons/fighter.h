#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <list>

#include "targetableobject.h"
#include "fighterproperties.h"
#include "objectmanager.h"
#include "ship.h"

//fighter class
//they mostly provide something for point defense to kill
class Fighter : public TargetableObject
{
public:
	static std::list<Fighter*> allFighters;

	Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTIONS faction,
		Ship *homeBase);
	virtual ~Fighter();
	virtual void run(f32 frameDeltaTime);

	//must override this 
	const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
protected:
	void rotate(f32 frameDeltaTime);
	void movement(f32 frameDeltaTime);
	void searchForFighterTargets();
	void patrol();

	std::list<Fighter*>::iterator it;

	int maxHull, hull;
	int maxVelocity, velocity;
	int maxTurn;
	unsigned maxFuel, fuel;
	vector3df targetRotation;
	Fighter *fighterTarget;
	Ship *homeBase;
};

#endif
