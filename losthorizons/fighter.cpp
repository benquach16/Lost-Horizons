#include "fighter.h"
#include <iostream>

std::list<Fighter*> Fighter::allFighters;

const unsigned PATROLDISTANCE = 500;
const unsigned AITIMER = 200;

//large constructor
Fighter::Fighter(const ObjectManager::E_FIGHTER_LIST fighterType, const vector3df& position, const vector3df& rotation, const E_GAME_FACTIONS faction, 
				 Ship* homeBase) : TargetableObject(nextID++, ObjectManager::fighterList[fighterType], position, rotation, faction), info(fighterType),
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
	if(info.hull > 1)
	{
		info.velocity = info.maxVelocity;
		rotate(frameDeltaTime);
		movement(frameDeltaTime);
		if(fighterTarget)
		{
			//if theres another fighter to fight
			//fly at it
			f32 dist = getPosition().getDistanceFromSQ(fighterTarget->getPosition());

			if(dist > 10000000)
			{
				vector3df diff = fighterTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				info.targetRotation = diff;
			}
			else if(dist < 40000)
			{
				vector3df diff = fighterTarget->getPosition() - getPosition();
				diff = diff.getHorizontalAngle();
				diff.Y += rand()%180+ 90;
				info.targetRotation = diff;
			}
			if(dist < 250000)
			{
				//close than 500 so we can shoot
				fighterTarget->damage(20);
			}
		}
		else
		{
			searchForFighterTargets();
			//patrol for targets around home ship
			if(homeBase)
			{

			}
		}

	}
	else
	{
		std::cout << info.hull <<std::endl;
		for(std::list<Fighter*>::iterator i = allFighters.begin(); i != allFighters.end(); ++i)
		{
			if((*i)->fighterTarget == this)
			{
				(*i)->fighterTarget = 0;
			}
		}
		delete this;
	}
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
	return E_OBJECT_FIGHTER;
}

//protected function
void Fighter::rotate(f32 frameDeltaTime)
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
void Fighter::movement(f32 frameDeltaTime)
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

	setPosition(sPos);
}

//protected function
void Fighter::searchForFighterTargets()
{
	for(std::list<Fighter*>::iterator i = allFighters.begin(), next; i != allFighters.end(); i = next)
	{
		next = i;
		next++;
		if(((*i)->faction == E_FACTION_PIRATE && faction != E_FACTION_PIRATE) || 
			((*i)->faction != E_FACTION_PIRATE && faction == E_FACTION_PIRATE))
		{
			if((*i)->getPosition().getDistanceFrom(getPosition()) < 5000)
			{
				fighterTarget = (*i);
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
