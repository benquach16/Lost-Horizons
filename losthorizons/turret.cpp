#include "stdafx.h"
#include "turret.h"
#include "ship.h"
#include <iostream>

//BEGIN TURRETSLOT
TurretSlot::TurretSlot(const turretInformation &properties, IBoneSceneNode *joint, const E_TURRET_CLASS &turretClass, Ship* parent) : 
	joint(joint), childTurret(0), properties(properties), rotationOffset(properties.rotation), parent(parent)
{
	//we have not one but two scene nodes beecause joints fuck things up
	offset = scenemngr->addEmptySceneNode(joint);
	aimPoint = scenemngr->addEmptySceneNode();
	offset->setRotation(rotationOffset);
}

void TurretSlot::assignTurret(const TurretProperties &props)
{
	//make sure that the childturret pointer is clear
	removeTurret();
	childTurret = new Turret(props, offset, this);
}

bool TurretSlot::getCanFire()
{
	return canFire;
}

bool TurretSlot::fire()
{
	if(childTurret && canFire)
	{
		childTurret->fire(currentAim);
		return true;
	}
	return false;
}

void TurretSlot::removeTurret()
{
	if(childTurret)
		delete childTurret;
	childTurret=0;
}

void TurretSlot::drawArc()
{
	//we're going to do some fun math here
}

void TurretSlot::aim(const core::vector3df &point, f32 frameDeltaTime)
{
	aimPoint->setPosition(joint->getAbsolutePosition());
	if(childTurret)
	{
		//do some math to find the angle to face this point
		/*
		const float x = (point.X-offset->getAbsolutePosition().X);
		const float y = (point.Y-offset->getAbsolutePosition().Y);
		const float z = (point.Z-offset->getAbsolutePosition().Z);
		float angleY = std::atan2(x,z)*static_cast<float>(180/3.1415);

		float tmp  = sqrt(x*x+z*z);
		float angleX = std::atan2(tmp,y)*static_cast<float>(180/3.1415);

		angleX -= 90;
		if(angleY>360) 
			angleY-=360;
		if(angleY < 0)
			angleY+=360;
		currentAim = vector3df(angleX, angleY,0);*/
		int difference = (360 - properties.arc)/2;
		
		vector3df diff = point - offset->getAbsolutePosition();
		diff = diff.getHorizontalAngle();
		currentAim = diff;
		//std::cout << offset->getAbsoluteTransformation().getRotationDegrees().Y << std::endl;

		//normalize angles
		float tmp = parent->getRotation().Y + 180 + rotationOffset.Y;
		if(tmp > 360)
			tmp -= 360;
		if(tmp < 0)
			tmp += 360;
		if((diff.Y + difference) < tmp || (diff.Y - difference) > tmp)
		{
			//inside the arc horizontally
			//pass rotation to the turret so we dont do math again unnecessarily
			//draw so player knows which turrets can shoot
			//angleY -= parent->getRotation().Y;
			//angleY += 180 - offset->getRotation().Y;
			diff.Y -= parent->getRotation().Y;
			diff.Y += 180 + offset->getRotation().Y;
			childTurret->aim(diff, frameDeltaTime);
			canFire = true;
		}
		else
		{
			//just reset the aim and not shoot
			//good shit
			childTurret->aim(vector3df(0,180,0), frameDeltaTime);
			canFire = false;
		}
	}
	else
	{
		//no turret so 
		canFire = false;
	}
}

void TurretSlot::resetAim()
{
	if(childTurret)
	{
		childTurret->aim(vector3df(0,180,0), 1);
		canFire = false;
	}
}

TurretSlot::~TurretSlot()
{
	//make sure we clear up memory
	removeTurret();
}

const Ship* TurretSlot::getParent() const
{
	return parent;
}

const vector3df& TurretSlot::getCurrentAim() const
{
	return currentAim;
}

const vector3df& TurretSlot::getPosition() const
{
	return aimPoint->getPosition();
}

//END TURRETSLOT


//BEGIN TURRET
Turret::Turret()
{
	//default constructor
}

Turret::Turret(const TurretProperties &props, ISceneNode *parent, TurretSlot *parentSlot) : 
	Object(props.getFilename().c_str(), vector3df(0,0,0), vector3df(0,0,0), props.getScale()), props(props), shootJoint(0),
	parentSlot(parentSlot)
{
	shootJoint = mesh->getJointNode("shoot");
	mesh->setParent(parent);
	setNormalMap(vdriver->getTexture(props.getNormalMap().c_str()));
}

Turret::~Turret()
{
	mesh->remove();
}

void Turret::aim(const core::vector3df &rotation, float frameDeltaTime)
{
	core::vector3df rot(getRotation());
	if(getRotation().Y < rotation.Y)
	{
		rot.Y += props.getMaxTurn() * frameDeltaTime;
	}
	if(getRotation().Y > rotation.Y)
	{
		rot.Y -= props.getMaxTurn() * frameDeltaTime;
	}
	rot.Y = rotation.Y;
	setRotation(rot);
}

void Turret::fire(const vector3df &rotation)
{
	//stopgap fix so we can have dynamically firing weapons
	//since volley fire looks pretty unrealistic
	//probably should modify this later
	if(rand() % (int)props.getReloadSpeed() < 3)
	{//for now, projectile gets an ID. change to ship pointer later
		Projectile *p = new Projectile(parentSlot->getParent()->getID(), props, shootJoint->getAbsolutePosition(), rotation);
		Muzzleflash *m = new Muzzleflash(shootJoint, getRotation());
		soundmngr->play3D(props.getSoundFilename().c_str(), getPosition());
	}
}

const Ship* Turret::getParent() const
{
	return parentSlot->getParent();
}
