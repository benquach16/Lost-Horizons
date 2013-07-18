#include "stdafx.h"
#include "turret.h"
#include "ship.h"
#include <iostream>


TurretSlot::TurretSlot() : joint(0), childTurret(0)
{
	//default constructor
}

TurretSlot::TurretSlot(const turretInformation &properties, IBoneSceneNode *joint, const E_TURRET_CLASS &turretClass, Ship* parent) : 
	joint(joint), childTurret(0), properties(properties), rotationOffset(properties.rotation), parent(parent)
{
	offset = scenemngr->addEmptySceneNode(joint);
	offset->setRotation(rotationOffset);
}

void TurretSlot::assignTurret(const TurretProperties &props)
{
	removeTurret();
	childTurret = new Turret(props, offset);
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
		int difference = properties.arc/2;
		angleY -= parent->getRotation().Y;
		angleY += 180;

		//if(angleToTarget.Y + difference < offset->getRotation().Y && angleToTarget.Y - difference > offset->getRotation().Y)
		{
			//inside the arc horizontally
			//pass rotation to the turret so we dont do math again unnecessarily
			childTurret->aim(vector3df(angleX, angleY, 0), frameDeltaTime);
		}
	}
}

TurretSlot::~TurretSlot()
{
}


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
		rot.Y += props.getMaxTurn();
	}
	if(getRotation().Y > rotation.Y)
	{
		rot.Y -= props.getMaxTurn();
	}
	rot.Y = rotation.Y;
	setRotation(rot);
}

Turret::~Turret()
{
}
