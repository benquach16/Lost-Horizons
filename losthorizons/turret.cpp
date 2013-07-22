#include "stdafx.h"
#include "turret.h"
#include "ship.h"
#include <iostream>

//BEGIN TURRETSLOT
TurretSlot::TurretSlot(const turretInformation &properties, IBoneSceneNode *joint, const E_TURRET_CLASS &turretClass, Ship* parent) : 
	joint(joint), childTurret(0), properties(properties), rotationOffset(properties.rotation), parent(parent), currentAim()
{
	offset = scenemngr->addEmptySceneNode(joint);
	aimPoint = scenemngr->addEmptySceneNode();
	offset->setRotation(rotationOffset);
}

void TurretSlot::assignTurret(const TurretProperties &props)
{
	removeTurret();
	childTurret = new Turret(props, offset);
}

bool TurretSlot::getCanFire()
{
	return canFire;
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
		//ensure if the point is inside firing arc
		const float x = (point.X-offset->getAbsolutePosition().X);
		const float y = (point.Y-offset->getAbsolutePosition().Y);
		const float z = (point.Z-offset->getAbsolutePosition().Z);
		float angleY = std::atan2(x,z)*static_cast<float>(180/3.1415);

		float tmp  = sqrt(x*x+z*z);
		float angleX = std::atan2(tmp,y)*static_cast<float>(180/3.1415);

		angleX -= 90;
		currentAim = vector3df(angleX, angleY,0);
		int difference = (360-properties.arc)/2;

		//angleY += 180;

		if(angleY + difference < offset->getAbsoluteTransformation().getRotationDegrees().Y || angleY - difference > offset->getAbsoluteTransformation().getRotationDegrees().Y)
		{
			//inside the arc horizontally
			//pass rotation to the turret so we dont do math again unnecessarily
			angleY -= parent->getRotation().Y;
			childTurret->aim(vector3df(angleX, angleY,0), frameDeltaTime);
			canFire = true;
		}
		else
		{
			//just reset the aim and not shoot
			//good shit
			childTurret->aim(vector3df(0,0,0), frameDeltaTime);
			canFire = false;
		}
	}
	else
	{
		//no turret so 
		canFire = false;
	}
}

TurretSlot::~TurretSlot()
{
	//make sure we clear up memory
	removeTurret();
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

Turret::Turret(const TurretProperties &props, ISceneNode *parent) : 
	Object(props.getFilename().c_str(), vector3df(0,0,0), vector3df(0,0,0), props.getScale()), props(props)
{
	mesh->setParent(parent);
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

Turret::~Turret()
{
}
