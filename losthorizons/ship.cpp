//#include "stdafx.h"
#include "ship.h"
#include <iostream>

std::list<Ship*> Ship::allShips;


Ship::Ship(E_GAME_FACTIONS faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation, bool isPlayer)
	: Object(ObjectManager::shipList[shipType].getFilename().c_str(), position, rotation,
	  ObjectManager::shipList[shipType].getScale()), isPlayer(isPlayer), info(shipType, faction)
{
	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();

	//set up the ship turrets
	initTurrets();
	setMediumTurret(ObjectManager::turretList[0],3);
}

Ship::Ship(const ShipInformation &info, const vector3df &position, const vector3df &rotation, bool isPlayer)
	: Object(ObjectManager::shipList[info.shipType].getFilename().c_str(), position, rotation,
	  ObjectManager::shipList[info.shipType].getScale()), isPlayer(isPlayer), info(info)
{
	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();

	//set up the ship turrets
	initTurrets();
	setMediumTurret(ObjectManager::turretList[0],3);
}

//copy constructor
Ship::Ship(const Ship *s) : isPlayer(s->isPlayer), info(s->info)
{
	allShips.push_front(this);
	it = allShips.begin();
}

Ship& Ship::operator=(const Ship *s)
{
	if (this != s)
	{

	}
	return *this;
}

Ship::~Ship()
{
	//destructor
	allShips.erase(it);
}

bool Ship::getIsPlayer()
{
	return isPlayer;
}

const ShipInformation& Ship::getInfo() const
{
	return info;
}

void Ship::run(f32 frameDeltaTime)
{
	Object::run();
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
		//mediumTurrets[3]->drawArc();
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
	for(unsigned i = 0; i < mediumTurrets.size(); i++)
	{
		if(mediumTurrets[i]->hasTurret())
		{
			Projectile *p = new Projectile(mediumTurrets[i]->getPosition(), mediumTurrets[i]->getCurrentAim(), ObjectManager::turretList[0]);
		}
	}
}

void Ship::setTargetRotationTo(const vector3df &newTargetRotation)
{
	info.targetRotation = newTargetRotation;
}

const vector3df &Ship::getTargetRotation() const
{
	return info.targetRotation;
}

void Ship::setTarget(Ship *newTarget)
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

//protected function
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

//protected function
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
//protected function
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

//protected function
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
	}
}
