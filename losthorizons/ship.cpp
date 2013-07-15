//#include "stdafx.h"
#include "ship.h"
#include <iostream>

std::list<Ship*> Ship::allShips;



Ship::Ship() : Object(0,L"", vector3df(0,0,0), vector3df(0,0,0))
{
}

Ship::Ship(const ShipProperties &props, const vector3df &position, const vector3df &rotation,
		   bool isPlayer) : 
	Object(props.getFilename().c_str(), position, rotation, props.getScale()), 
		isPlayer(isPlayer), props(props), currentAIState(STATE_PATROLLING),
		maxHull(props.getHull()), hull(props.getHull()), maxVelocity(props.getMaxVel()), velocity(0.0f),
		maxTurn((f32)props.getMaxTurn())
{
	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();

	//set up the ship turrets
	initTurrets();
	setMediumTurret(ObjectManager::turretList[0],3);
}

//copy constructor
Ship::Ship(const Ship *s) : isPlayer(s->isPlayer), props(s->props), currentAIState(s->currentAIState),
		maxHull(s->maxHull), hull(s->hull), maxVelocity(s->maxVelocity), velocity(s->velocity), maxTurn(s->maxTurn)
{
	allShips.push_front(this);
	it = allShips.begin();
}

Ship& Ship::operator=(const Ship *s)
{
	if(this != s)
	{
	}
	return *this;
}

Ship::~Ship()
{
	//destructor
	allShips.erase(it);
}

void Ship::removeAI()
{
	//deletes itself if it is an AI
	if(!isPlayer)
		delete this;
}

void Ship::run(f32 frameDeltaTime)
{
	Object::run();
	if(hull > 0)
	{
		//make sure its alive to do anything
		//make it rotate to its targetted rotation first
		//and movement
		rotate(frameDeltaTime);
		movement(frameDeltaTime);

		//aim turrets
		//mediumTurrets[3]->drawArc();
	}

}

//increases velocity based on how fast the ship is going
void Ship::increaseVelocity(f32 frameDeltaTime)
{
	if(velocity < maxVelocity)
	{
		velocity+=(5+abs(velocity)/2)*frameDeltaTime;
	}
}

void Ship::decreaseVelocity(f32 frameDeltaTime)
{
	if(velocity > -maxVelocity)
	{
		velocity-=(1+abs(velocity)/2)*frameDeltaTime;
	}
}

void Ship::setTargetRotationTo(const vector3df &newTargetRotation)
{
	targetRotation = newTargetRotation;
}

const vector3df &Ship::getTargetRotation() const
{
	return targetRotation;
}

void Ship::setMediumTurret(const TurretProperties &props, int slot)
{
	mediumTurrets[slot]->assignTurret(props);
}

ShipData Ship::getShipData()
{
	ShipData tmp;
	tmp.hull = hull;
	tmp.armor = armor;
	tmp.shield = shield;
	tmp.maxHull = maxHull;
	tmp.maxArmor = maxArmor;
	tmp.maxShield = maxShield;
	tmp.crew = crew;
	tmp.maxCrew = maxCrew;
	tmp.velocity = velocity;
	tmp.maxVelocity = maxVelocity;
	tmp.maxTurn = maxTurn;
	tmp.position = getPosition();
	tmp.rotation = getRotation();
	tmp.targetRotation = targetRotation;
	tmp.currentAIState = currentAIState;
	tmp.currentFaction = currentFaction;
	return tmp;
}

//protected function
//rotates ship to point
void Ship::rotate(f32 frameDeltaTime)
{
	vector3df sRot = getRotation();
	vector3df rotSlow = getRotation();
	if(getRotation().Y<targetRotation.Y)	//ship wants to rotate right
	{
		rotSlow.Y=0.5f*(abs(getRotation().Y-targetRotation.Y));	//simulate inertia
		rotSlow.Z=0.5f*(abs(getRotation().Y-targetRotation.Y));
		if(rotSlow.Z>4)
			rotSlow.Z=4.f;
		if(rotSlow.X>4)
			rotSlow.X=4.f;
		if(rotSlow.Y>maxTurn)
			rotSlow.Y=maxTurn;
		sRot.Y+=rotSlow.Y*frameDeltaTime;
		sRot.Z=-rotSlow.Z;
		setRotation(sRot);
	}
	if(getRotation().Y>targetRotation.Y)	//ship wants to rotate left
	{
		rotSlow.Y=0.5f*(abs(getRotation().Y-targetRotation.Y));	//simulate inertia
		rotSlow.Z=0.5f*(abs(getRotation().Y-targetRotation.Y));
		if(rotSlow.Z>4)
			rotSlow.Z=4;
		if(rotSlow.Y>maxTurn)
			rotSlow.Y=maxTurn;
		sRot.Y-=rotSlow.Y*frameDeltaTime;
		sRot.Z=rotSlow.Z;
		setRotation(sRot);
	}
	if(getRotation().X>targetRotation.X)	//turn up
	{
		sRot=getRotation();
		rotSlow.X=0.5f*(abs(getRotation().X-targetRotation.X));
		if(rotSlow.X>maxTurn)
			rotSlow.X=maxTurn;
		sRot.X-=rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
	if(getRotation().X<targetRotation.X)	//turn down
	{
		sRot=getRotation();
		rotSlow.X=0.5f*(abs(getRotation().X-targetRotation.X));
		if(rotSlow.X>maxTurn)
			rotSlow.X=maxTurn;
		sRot.X+=rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
	
}

//protected function
void Ship::movement(f32 frameDeltaTime)
{
	vector3df sPos = getPosition();
	f32 i = getRotation().Y;
	f32 z = -(getRotation().X);	//if i dont do this the ship doesnt rotate right


	sPos.Y = (f32)(frameDeltaTime*velocity*(sin(z * 3.14/180)));
	sPos.Y+=getPosition().Y;

	sPos.X = (f32)(frameDeltaTime*velocity*(sin(i * 3.14/180)));
	sPos.X+=getPosition().X;

	sPos.Z = (f32)(frameDeltaTime*velocity*(cos(i * 3.14/180)));
	sPos.Z+=getPosition().Z;

	//smooth out ship movement
	vector3df finalPos = sPos*0.8f + getPosition() *0.2f;
	setPosition(finalPos);
}

//protected function
//initialises the turret slot classes for each ship
void Ship::initTurrets()
{
	//we create new turret slots and assign them tot he ship
	for(int i = 0; i < props.getMaxMTurrets(); i++)
	{
		//get the bone name and set it to the string
		std::string jointName("turret_0");
		std::string tmp = std::to_string(i+1);
		jointName+=tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(props.mediumTurrets[i], joint);
		mediumTurrets.push_back(t);
	}
}
