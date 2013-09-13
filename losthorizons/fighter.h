#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include <list>

#include "targetableobject.h"
#include "fighterproperties.h"
#include "objectmanager.h"
#include "ship.h"


//fighter info struct
struct FighterInformation
{
	ObjectManager::E_FIGHTER_LIST fighterType;
	int maxHull, hull;
	f32 maxVelocity, velocity;
	f32 maxTurn;
	unsigned maxFuel, fuel;
	vector3df targetRotation;
	FighterInformation() {}
	FighterInformation(ObjectManager::E_FIGHTER_LIST fighterType) 
		: maxHull(ObjectManager::fighterList[fighterType].getMaxHull()), hull(maxHull),
		maxVelocity(ObjectManager::fighterList[fighterType].getMaxVelocity()), velocity(0),
		maxTurn(ObjectManager::fighterList[fighterType].getMaxTurn()),
		maxFuel(ObjectManager::fighterList[fighterType].getMaxFuel()), fuel(maxFuel)
	{}
};

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
	void damage(int modifier);
	//must override this 
	const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
protected:
	//protected functions
	void rotate(f32 frameDeltaTime);
	void movement(f32 frameDeltaTime);
	void searchForFighterTargets();
	void patrol();

	//iterator to this
	std::list<Fighter*>::iterator it;

	FighterInformation info;
	Fighter *fighterTarget;
	Ship *shipTarget;
	Ship *homeBase;

	//create timekeeping variables
	u32 shootTimer;
};

#endif
