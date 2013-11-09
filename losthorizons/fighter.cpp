#include "stdafx.h"
#include "fighter.h"
#include "globals.h"
#include <iostream>

using namespace base;

std::vector<Fighter*> Fighter::allFighters;

#define PATROLDISTANCE 500
#define AITIMER 200

//large constructor
Fighter::Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTION faction, 
				 Ship* homeBase) : TargetableObject(nextID++, *ObjectManager::fighterList[fighterType], position, rotation, faction), info(fighterType),
	fighterTarget(0), homeBase(homeBase), shipTarget(0), shootTimer(0), index(allFighters.size())
{
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Fighter object created" << std::endl;

	allFighters.push_back(this);
}

Fighter::~Fighter()
{
	for (unsigned i = 0; i < allFighters.size(); ++i) {
		if (allFighters[i]->fighterTarget == this) {
			allFighters[i]->fighterTarget = 0;
		}
	}
	allFighters[index] = allFighters.back();
	allFighters[index]->index = index;
	allFighters.pop_back();
}

bool Fighter::run()
{
	//run basic control and ai here
	if (info.hull > 1) {
		rotate();
		movement();
		if (fighterTarget) {
			//if theres another fighter to fight
			//fly at it
			const f32 dist = getPosition().getDistanceFromSQ(fighterTarget->getPosition());

			if (dist > 25000) {
				info.targetRotation = (fighterTarget->getPosition() - getPosition()).getHorizontalAngle();
			} else if (dist < 4000) {
				info.targetRotation = (fighterTarget->getPosition() - getPosition()).getHorizontalAngle() + vector3df(0,(f32)(rand()%180 + 90),0);
			}
			if (dist < 250000) {
				//close than 500 so we can shoot
				if (shootTimer < timer->getTime()) {
					fighterTarget->damage(2);
					shootTimer = timer->getTime() + 1000;
				}
			}
		}
		else if (shipTarget) {
			//attack the ship
			searchForFighterTargets();
			const f32 dist = getPosition().getDistanceFromSQ(shipTarget->getPosition());
			if (dist > 250000) {
				info.targetRotation = (shipTarget->getPosition() - getPosition()).getHorizontalAngle();
			} else if (dist < 40000) {
				info.targetRotation = (shipTarget->getPosition() - getPosition()).getHorizontalAngle() + vector3df(0,(f32)(rand()%180 + 90),0);
			}
			if (dist < 250000) {
				//fire projectile or missile
			}
		}
		else {
			searchForFighterTargets();
			searchForShipTargets();
			//patrol for targets around home ship
			if (homeBase) {

			}
		}

	}
	else {
		remove();
	}
	return TargetableObject::run();
}

void Fighter::damage(int damage)
{
	if (info.hull > 0) {
		info.hull -= damage;
	}
}

const E_TARGETABLEOBJECT_TYPE Fighter::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_FIGHTER;
}

//protected function
void Fighter::rotate()
{
	vector3df currentRot = getRotation();
	if (currentRot != info.targetRotation) {
		if (currentRot.Y != info.targetRotation.Y) {
			f32 slowY = currentRot.Z = 0.5f*abs(currentRot.Y - info.targetRotation.Y);
			if (slowY > info.maxTurn)
				slowY = info.maxTurn;
			if (currentRot.Z > 4)
				currentRot.Z = 4.f;
			if (currentRot.Y < info.targetRotation.Y) {
				//rotate right
				currentRot.Y += slowY*frameDeltaTime;
				currentRot.Z = -currentRot.Z;
			} else {
				//rotate left
				currentRot.Y -= slowY*frameDeltaTime;
			}
		}
		if (currentRot.X != info.targetRotation.X) {
			f32 slowX = 0.5f*abs(currentRot.X - info.targetRotation.X);
			if (slowX > info.maxTurn)
				slowX = info.maxTurn;
			if (currentRot.X > info.targetRotation.X) {
				//rotate up
				currentRot.X -= slowX*frameDeltaTime;
			} else {
				//rotate down
				currentRot.X += slowX*frameDeltaTime;
			}
		}
		setRotation(currentRot);
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
	for (unsigned i = 0; i < allFighters.size(); ++i) {
		if (allFighters[i]->faction != faction &&
			(faction == FACTION_PIRATE || allFighters[i]->faction == FACTION_PIRATE) &&
			allFighters[i]->getPosition().getDistanceFrom(getPosition()) < 1000) {
			fighterTarget = allFighters[i];
		}
	}
}

//protected function
void Fighter::searchForShipTargets()
{
	for (unsigned i = 0; i < Ship::allShips.size(); ++i) {
		if (Ship::allShips[i]->getFaction() != faction &&
			(faction == FACTION_PIRATE || Ship::allShips[i]->getFaction() == FACTION_PIRATE) &&
			Ship::allShips[i]->getPosition().getDistanceFrom(getPosition()) < 5000) {
			shipTarget = Ship::allShips[i];
		}
	}
}

//protected function
void Fighter::patrol()
{
	if (getPosition().getDistanceFrom(homeBase->getPosition()) > PATROLDISTANCE) {
		//too far from home so reorient

	}
}
