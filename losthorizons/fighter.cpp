#include "fighter.h"
#include <iostream>

std::list<Fighter*> Fighter::allFighters;

const unsigned PATROLDISTANCE = 500;

//large constructor
Fighter::Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTIONS faction, u32 homeBaseID,
				 Ship* homeBase) : TargetableObject(nextID++, ObjectManager::fighterList[fighterType], position, rotation, faction), 
				 hull(ObjectManager::fighterList[fighterType].getMaxHull()),
	maxHull(ObjectManager::fighterList[fighterType].getMaxHull()),
	maxVelocity(ObjectManager::fighterList[fighterType].getMaxVelocity()),
	fighterTarget(0), homeBase(homeBase)
{
	allFighters.push_front(this);
	it = allFighters.begin();
	std::cout << '[' << ID << "]Fighter object created" << std::endl;
}

Fighter::~Fighter()
{
	allFighters.erase(it);
}

void Fighter::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
	//run basic control and ai here
	if(hull > 1)
	{
		rotate(frameDeltaTime);
		movement(frameDeltaTime);
		if(fighterTarget)
		{
			//if theres another fighter to fight
		}
		else
		{
			//patrol for targets around home ship
			if(homeBase)
			{

			}
		}
	}
	else
	{
		std::cout << hull <<std::endl;
		delete this;
	}
}

const E_TARGETABLEOBJECT_TYPE Fighter::getTargetableObjectType() const
{
	return E_OBJECT_FIGHTER;
}

//protected function
void Fighter::rotate(f32 frameDeltaTime)
{
}

//protected function
void Fighter::movement(f32 frameDeltaTime)
{
	vector3df sPos = getPosition();
	f32 i = getRotation().Y;
	f32 z = -(getRotation().X);	//if i dont do this the ship doesnt rotate right

	sPos.Y = (f32)(frameDeltaTime*velocity*(sin(z*3.14/180)));
	sPos.Y += getPosition().Y;

	sPos.X = (f32)(frameDeltaTime*velocity*(sin(i*3.14/180)));
	sPos.X += getPosition().X;

	sPos.Z = (f32)(frameDeltaTime*velocity*(cos(i*3.14/180)));
	sPos.Z += getPosition().Z;

	setPosition(sPos);
}

//protected function
void Fighter::searchForFighterTargets()
{
	for(std::list<Fighter*>::iterator i = allFighters.begin(); i != allFighters.end(); ++i)
	{

	}
}

//protected function
void Fighter::patrol()
{
	if(getPosition().getDistanceFrom(homeBase->getPosition()) > PATROLDISTANCE)
	{
		//too far from home so reorient
	}
}
