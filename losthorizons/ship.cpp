#include "stdafx.h"
#include "ship.h"
#include <iostream>

std::list<Ship*> Ship::allShips;

Ship::Ship(E_GAME_FACTIONS faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, ObjectManager::shipList[shipType], position, rotation), info(shipType, faction), shipTarget(0)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Ship object created" << std::endl;

	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();
	
	//set up the ship turrets
	initTurrets();
	setNormalMap(vdriver->getTexture(ObjectManager::shipList[shipType].getNormalMap().c_str()));
	setMediumTurret(ObjectManager::turretList[0],3);
	setMediumTurret(ObjectManager::turretList[0],1);
}

Ship::Ship(u32 ID, const ShipInformation &info, const vector3df &position, const vector3df &rotation)
	: TargetableObject(ID, ObjectManager::shipList[info.shipType], position, rotation), info(info), shipTarget(0)
{
	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();

	//set up the ship turrets
	initTurrets();
}

//copy constructor
Ship::Ship(const Ship *s, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, ObjectManager::shipList[s->info.shipType], position, rotation), info(s->info), shipTarget(0)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();
}

//assignmennt operator
Ship& Ship::operator=(const Ship *s)
{
	if (this != s)
	{
		//TODO: ASSISNGMENT OPERATOR!!!

	}
	return *this;
}

Ship::~Ship()
{
	allShips.erase(it);
}

void Ship::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
	if (info.hull > 0)
	{
		//make sure its alive to do anything
		//if the crew is 0 the ship is effectively dead
		//make it rotate to its targetted rotation first
		//and movement

		rotate(frameDeltaTime);
		aimTurrets(frameDeltaTime);

		movement(frameDeltaTime);

		//aim turrets

		//if is not player do ai stuff
		if (!isPlayer())
		{
			runAI();
		}
	}
	else
	{
		//we have to delete this ship when it asplodes
		//so create an explosion and delete itself
		removeThisFromTargets();
		delete this;
	}
}

//increases velocity based on how fast the ship is going
void Ship::increaseVelocity(f32 frameDeltaTime)
{
	if (info.velocity < info.maxVelocity)
		info.velocity += (5+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::decreaseVelocity(f32 frameDeltaTime)
{
	if (info.velocity > -info.maxVelocity)
		info.velocity -= (1+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::fireTurrets()
{
	//lets do this in a way that doesn't involve middlemen
	for (unsigned i = 0; i < mediumTurrets.size(); ++i) {
		mediumTurrets[i]->fire();
	}
}

void Ship::damage(int val)
{
	//do damage stuff here
	//check shields, then armor then hull
	if(info.shield > 0)
	{
		info.shield -= val;
	}
	else if(info.armor > 0)
	{
		info.armor -= val;
	}
	else
	{
		//damage hull
		info.hull -= val;
	}
}

void Ship::setTargetRotation(const vector3df &newTargetRotation)
{
	info.targetRotation = newTargetRotation;
}

const vector3df &Ship::getTargetRotation() const
{
	return info.targetRotation;
}

void Ship::setTarget(TargetableObject *newTarget)
{
	shipTarget = newTarget;
}

void Ship::removeTarget()
{
	shipTarget = 0;
}

void Ship::setMediumTurret(const TurretProperties &props, int slot)
{
	mediumTurrets[slot]->assignTurret(props);
}

void Ship::setFaction(E_GAME_FACTIONS newFaction)
{
	info.currentFaction = newFaction;
}

const ShipInformation& Ship::getInfo() const
{
	return info;
}

const TargetableObject* Ship::getShipTarget() const
{
	return shipTarget;
}

bool Ship::isPlayer() const
{
	return ID == 0;
}

void Ship::removeThisFromTargets()
{
	//loop thru ship lista nd remove this ship if it is a target
	for(std::list<Ship*>::iterator i = allShips.begin(); i != allShips.end(); i++)
	{
		if((*i)->getShipTarget() == this)
		{
			(*i)->setTarget(0);
		}
	}
}

//private function
//rotates ship to point
void Ship::rotate(f32 frameDeltaTime)
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

//private function
void Ship::movement(f32 frameDeltaTime)
{
	vector3df sPos = getPosition();
	f32 i = getRotation().Y;
	f32 z = -(getRotation().X);	//if i dont do this the ship doesnt rotate right

	sPos.Y = (f32)(frameDeltaTime*info.velocity*(sin(z*3.14/180)));
	sPos.Y += getPosition().Y;

	sPos.X = (f32)(frameDeltaTime*info.velocity*(sin(i*3.14/180)));
	sPos.X += getPosition().X;

	sPos.Z = (f32)(frameDeltaTime*info.velocity*(cos(i*3.14/180)));
	sPos.Z += getPosition().Z;

	//smooth out ship movement
	vector3df finalPos = sPos*0.8f+getPosition()*0.2f;
	setPosition(finalPos);
}
//private function
//initialises the turret slot classes for each ship
void Ship::initTurrets()
{
	//we create new turret slots and assign them to the ship
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxHTurrets(); ++i)
	{

	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxMTurrets(); ++i)
	{
		//get the bone name and set it to the string
		std::string jointName("turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType].mediumTurrets[i], joint, E_CLASS_MEDIUM, this);
		mediumTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxLTurrets(); ++i)
	{
	}
}

//private function
//aims turrets at current target
void Ship::aimTurrets(float frameDeltaTime)
{
	if (shipTarget)
	{
		//if has target
		for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		{
			mediumTurrets[i]->aim(shipTarget->getPosition(), frameDeltaTime);
		}
	}
	else
	{
		//go back to aiming like normal
		for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		{
			mediumTurrets[i]->resetAim();
		}
	}
}

//private function
//do all AI stuff here
void Ship::runAI()
{
	updateStates();
	if(info.currentAIState == STATE_FLEEING)
	{
		//do fleeing code here
	}
	else if(info.currentAIState == STATE_ATTACKING)
	{
		//do attacking code here
		if(shipTarget)
		{

		}
		else
		{
			//if theres no target, change the state
		}
	}
	else if(info.currentAIState == STATE_PATROLLING)
	{
		//crooze
		info.velocity = info.maxVelocity/2;
	}
}

//private function
void Ship::updateStates()
{
	if(info.hull < info.maxHull/2)
	{
		//if hull is less than half, try to flee
		info.currentAIState = STATE_FLEEING;
	}

}
