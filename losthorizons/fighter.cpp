#include "stdafx.h"
#include "fighter.h"
#include "globals.h"
#include <iostream>

using namespace base;

std::list<Fighter*> Fighter::allFighters;

const unsigned PATROLDISTANCE = 500;
const unsigned AITIMER = 200;

//large constructor
Fighter::Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTION faction, 
				 Ship* homeBase) : TargetableObject(nextID++, *ObjectManager::fighterList[fighterType], position, rotation, faction), info(fighterType),
	fighterTarget(0), homeBase(homeBase), shipTarget(0), shootTimer(0)
{
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Fighter object created" << std::endl;

	allFighters.push_front(this);
	it = allFighters.begin();
}

Fighter::~Fighter()
{
	for(std::list<Fighter*>::iterator i = allFighters.begin(); i != allFighters.end(); ++i)
	{
		if((*i)->fighterTarget == this)
		{
			(*i)->fighterTarget = 0;
		}
	}
	allFighters.erase(it);
}

bool Fighter::run()
{
	//run basic control and ai here
	if(info.hull > 1)
	{
		info.velocity = info.maxVelocity;
		rotate();
		movement();
		if(fighterTarget)
		{
			//if theres another fighter to fight
			//fly at it
			f32 dist = getPosition().getDistanceFromSQ(fighterTarget->getPosition());

			if(dist > 25000)
			{
				vector3df diff = fighterTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				info.targetRotation = diff;
			}
			else if(dist < 4000)
			{
				vector3df diff = fighterTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				diff.Y += rand()%180+ 90;
				info.targetRotation = diff;
			}
			if(dist < 250000)
			{
				//close than 500 so we can shoot
				if(shootTimer < timer->getTime())
				{
					fighterTarget->damage(2);
					shootTimer = timer->getTime() + 1000;
				}
			}
		}
		else if(shipTarget)
		{
			//attack the ship
			searchForFighterTargets();
			f32 dist = getPosition().getDistanceFromSQ(shipTarget->getPosition());
			if(dist > 250000)
			{
				vector3df diff = shipTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				info.targetRotation = diff;
			}
			else if(dist < 40000)
			{
				vector3df diff = shipTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				diff.Y += rand()%180+ 90;
				info.targetRotation = diff;
			}
			if(dist < 250000)
			{
				//fire projectile or missile
			}
		}
		else
		{
			searchForFighterTargets();
			searchForShipTargets();
			//patrol for targets around home ship
			if(homeBase)
			{

			}
		}

	}
	else
	{
		remove();
	}
	return TargetableObject::run();
}

void Fighter::damage(int modifier)
{
	if(info.hull > 0)
	{
		info.hull -= modifier;
	}
}

const E_TARGETABLEOBJECT_TYPE Fighter::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_FIGHTER;
}

//protected function
void Fighter::rotate()
{
	vector3df sRot = getRotation();
	vector3df rotSlow = getRotation();
	if (getRotation().Y < info.targetRotation.Y)	//ship wants to rotate right
	{
		rotSlow.Y = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));	//simulate inertia
		rotSlow.Z = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));
		if (rotSlow.Z > 4)
			rotSlow.Z = 4.f;
		if (rotSlow.X > 4)
			rotSlow.X = 4.f;
		if (rotSlow.Y > info.maxTurn)
			rotSlow.Y = info.maxTurn;
		sRot.Y += rotSlow.Y*frameDeltaTime;
		sRot.Z = -rotSlow.Z;
		setRotation(sRot);
	}
	if (getRotation().Y > info.targetRotation.Y)	//ship wants to rotate left
	{
		rotSlow.Y = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));	//simulate inertia
		rotSlow.Z = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));
		if (rotSlow.Z > 4)
			rotSlow.Z = 4;
		if (rotSlow.Y > info.maxTurn)
			rotSlow.Y = info.maxTurn;
		sRot.Y -= rotSlow.Y*frameDeltaTime;
		sRot.Z = rotSlow.Z;
		setRotation(sRot);
	}
	if (getRotation().X > info.targetRotation.X)	//turn up
	{
		sRot = getRotation();
		rotSlow.X = 0.5f*(abs(getRotation().X-info.targetRotation.X));
		if (rotSlow.X > info.maxTurn)
			rotSlow.X = info.maxTurn;
		sRot.X -= rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
	if (getRotation().X < info.targetRotation.X)	//turn down
	{
		sRot = getRotation();
		rotSlow.X = 0.5f*(abs(getRotation().X-info.targetRotation.X));
		if (rotSlow.X > info.maxTurn)
			rotSlow.X = info.maxTurn;
		sRot.X += rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
}

//protected function
void Fighter::movement()
{
	const f32 temp = frameDeltaTime*info.velocity;
	const f32 X = sin(getRotation().Y*PI/180)*temp + getPosition().X;
	const f32 Y = sin(-getRotation().X*PI/180)*temp + getPosition().Y;
	const f32 Z = cos(getRotation().Y*PI/180)*temp + getPosition().Z;
	setPosition(core::vector3df(X,Y,Z));
}

//protected function
void Fighter::searchForFighterTargets()
{
	for(std::list<Fighter*>::iterator i = allFighters.begin(), next; i != allFighters.end(); i = next)
	{
		next = i;
		next++;
		if(((*i)->faction == FACTION_PIRATE && faction != FACTION_PIRATE) || 
			((*i)->faction != FACTION_PIRATE && faction == FACTION_PIRATE))
		{
			if((*i)->getPosition().getDistanceFrom(getPosition()) < 1000)
			{
				fighterTarget = (*i);
			}
		}
	}
}

//protected function
void Fighter::searchForShipTargets()
{
	for (unsigned i = 0; i < Ship::allShips.size(); i++)
	{
		if((Ship::allShips[i]->getFaction() == FACTION_PIRATE && faction != FACTION_PIRATE) || 
			(Ship::allShips[i]->getFaction() != FACTION_PIRATE && faction == FACTION_PIRATE))
		{
			if(Ship::allShips[i]->getPosition().getDistanceFrom(getPosition()) < 5000)
			{
				shipTarget = (Ship::allShips[i]);
			}
		}
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
