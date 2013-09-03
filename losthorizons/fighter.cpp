#include "fighter.h"

std::list<Fighter*> Fighter::allFighters;

Fighter::Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTIONS faction, u32 homeBaseID) : 
	TargetableObject(nextID++, ObjectManager::fighterList[fighterType], position, rotation, faction)
{
	allFighters.push_front(this);
	it = allFighters.begin();
}

Fighter::~Fighter()
{
	allFighters.erase(it);
}

void Fighter::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
	//run basic control and ai here
	if(hull > 0)
	{

	}
	else
	{
		delete this;
	}
}
