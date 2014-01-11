#ifndef _FIGHTER_H_
#define _FIGHTER_H_

#include "targetableobject.h"
#include "fighterproperties.h"
#include "objectmanager.h"
#include "ship.h"

enum E_FIGHTER_STANCE
{
	FIGHTER_STANCE_ATTACK,
	FIGHTER_STANCE_DEFEND,
	//ignore fighter targets
	FIGHTER_STANCE_ATTACK_IGNORE,
};

//fighter info struct
struct FighterInformation
{
	ObjectManager::E_FIGHTER_LIST fighterType;
	int maxHull, hull;
	f32 velocity, maxTurn;
	unsigned maxFuel, fuel;
	vector3df targetRotation;
	E_FIGHTER_STANCE currentStance;
	FighterInformation() {}
	FighterInformation(ObjectManager::E_FIGHTER_LIST fighterType) 
		: maxHull(ObjectManager::fighterList[fighterType]->getMaxHull()), hull(maxHull),
		velocity(ObjectManager::fighterList[fighterType]->getMaxVelocity()),
		maxTurn(ObjectManager::fighterList[fighterType]->getMaxTurn()),
		maxFuel(ObjectManager::fighterList[fighterType]->getMaxFuel()), fuel(maxFuel),
		currentStance(FIGHTER_STANCE_DEFEND)
	{}
};

//fighter class
//they mostly provide something for point defense to kill
class Fighter : public TargetableObject
{
public:
	static std::vector<Fighter*> allFighters;

	Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTION faction,
		Ship *homeBase);
	virtual ~Fighter();
	virtual bool run();
	void damage(int damage);
	//must override this 
	const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;

protected:
	FighterInformation info;
	Fighter *fighterTarget;
	Ship *shipTarget;
	Ship *homeBase;

	//protected functions
	void rotate();
	void movement();

private:
	void searchForFighterTargets();
	void searchForShipTargets();
	void patrol();

	//create timekeeping variables
	u32 shootTimer;

	//iterator to this
	int index;
};

#endif
