#include "stdafx.h"
#include "globals.h"
#include "missile.h"
#include "impact.h"

std::vector<Missile*> Missile::allMissiles;

using namespace base;
using namespace core;
using namespace video;

const int MISSILETIMER = 1500;

Missile::Missile(const u16 ID, const TargetableObject *target, const TurretProperties &turretProps,
				 const vector3df &position, const vector3df &rotation)
				 : Projectile(ID, turretProps, position, rotation),
				   target(target), health(30), index(allMissiles.size())
{
	// TODO: all projectiles should have a timer; do this the same way effects are done
	missileTimer = timer->getTime() + MISSILETIMER;
	initMissile();
	allMissiles.push_back(this);
}

Missile::~Missile()
{
	exhaust->remove();
	allMissiles[index] = allMissiles.back();
	allMissiles[index]->index = index;
	allMissiles.pop_back();
}

bool Missile::run()
{
	//fly torwards the target
	//but not liike too fast you know
	if (target)
	{
		if(!target->getActive())
		{
			target = 0;
			remove();
			return Projectile::run();
		}
		if(missileTimer < timer->getTime())
		{
		
			vector3df targetRotation = target->getPosition() - getPosition();
			targetRotation = targetRotation.getHorizontalAngle();
			//TODO delta time and rotation speed
			vector3df rot(getRotation());
			//THIS CODE IS VERY CORRECT
			//MAKE SURE TO SWAP OTHER ROTATION CODES WITH THIS EVENTUALLY
			if(targetRotation.X > getRotation().X || (getRotation().X > 270 && targetRotation.X < 90))
			{
				rot.X += 0.5f;
			}
			else if(targetRotation.X < getRotation().X || (targetRotation.X > 270 && getRotation().X < 90))
			{
				rot.X -= 0.5f;
			}
			if(targetRotation.Y > getRotation().Y || (getRotation().Y > 270 && targetRotation.Y < 90))
			{
				rot.Y += 0.5f;
			}
			else if(targetRotation.Y < getRotation().Y || (targetRotation.Y > 270 && getRotation().Y < 90))
			{
				rot.Y -= 0.5f;
			}
			if(rot.X < 0)
			{
				rot.X += 360;
			}
			if(rot.X > 360)
			{
				rot.X -= 360;
			}
			if(rot.Y < 0)
			{
				rot.Y += 360;
			}
			if(rot.Y > 360)
			{
				rot.Y -= 360;
			}
			setRotation(rot);
		}
		else
		{
			setRotation(getRotation() + vector3df(-0.5,0,0));
		}

	}
	else
	{
		// it will detonate itself if the target is gone
		// alternatively, it could be set to just fly straight until it
		// hits something else or its timer is reached
		// or we could think of something fancier such as behavior depends
		// on the type of missile :^)
		remove();
	}
	return Projectile::run();
}

void Missile::damage(int damage)
{
	health -= damage;
	if(health < 1)
	{
		new Impact(getPosition());
		remove();
	}
}

void Missile::setTarget(TargetableObject *newTarget)
{
	target = newTarget;
}

const TargetableObject* Missile::getCurrentTarget() const
{
	return target;
}

void Missile::initMissile()
{
	exhaust=scenemngr->addParticleSystemSceneNode(false, mesh);
	scene::IParticleEmitter *em = exhaust->createPointEmitter(vector3df(0,0,0),
		50,100,
		SColor(255,255,255,255),
		SColor(255,255,255,255),
		1000,
		1000,
		0,
		dimension2df(5,5),
		dimension2df(15,15));
	exhaust->setEmitter(em);
	em->drop();
	exhaust->setMaterialTexture(0,vdriver->getTexture("res/textures/engine_trails.pcx"));
	exhaust->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	exhaust->setMaterialFlag(video::EMF_LIGHTING,false);
}
