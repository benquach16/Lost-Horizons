#include "stdafx.h"
#include "globals.h"
#include "missile.h"

std::vector<Missile*> Missile::allMissiles;

using namespace base;
using namespace core;
using namespace video;

const int MISSILETIMER = 1500;

Missile::Missile(const u16 ID, const TargetableObject *target, const TurretProperties &turretProps, 
		const vector3df &position, 
		const vector3df &rotation) : 
Projectile(ID, turretProps,
		   position,
		   rotation),
		   target(target)
{
	missileTimer = timer->getTime() + MISSILETIMER;
	initMissile();
	index = allMissiles.size();
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
	if(missileTimer < timer->getTime())
	{
		vector3df targetRotation = target->getPosition() - getPosition();
		targetRotation = targetRotation.getHorizontalAngle();
		//TODO delta time and rotation speed
		vector3df rot(getRotation());
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
	return Projectile::run();
}

void Missile::initMissile()
{
	exhaust=scenemngr->addParticleSystemSceneNode(false, mesh);
	scene::IParticleEmitter *em = exhaust->createPointEmitter(vector3df(0,0,0),
		20,40,
		SColor(255,255,255,255),
		SColor(255,255,255,255),
		1000,
		2000,
		0,
		dimension2df(5,5),
		dimension2df(15,15));
	exhaust->setEmitter(em);
	em->drop();
	exhaust->setMaterialTexture(0,vdriver->getTexture("res/textures/engine_trails.pcx"));
	exhaust->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	exhaust->setMaterialFlag(video::EMF_LIGHTING,false);
}
