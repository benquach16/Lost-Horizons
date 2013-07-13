#include "stdafx.h"
#include "turret.h"


TurretSlot::TurretSlot() : joint(0), childTurret(0)
{
	//default constructor
}

TurretSlot::TurretSlot(const turretInformation &properties, IBoneSceneNode *joint) : joint(joint), childTurret(0),
	properties(properties), rotationOffset(properties.rotation), graphics(graphics)
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
	int difference = properties.arc/2;
	core::vector3df base;
	core::vector3df second(base);
	core::vector3df third(base);
	second.X = (f32)(sin((difference) * 3.141 / 180) * (200.f));
	second.Z = (f32)(cos((difference) * 3.141/ 180) * (200.f)); 
	third.X = (f32)(sin((-difference) * 3.141 / 180) * (200.f));
	third.Z = (f32)(cos((-difference) * 3.141/ 180) * (200.f)); 

	vdriver->draw3DTriangle(triangle3df(base, second, third));
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
	Object(props.getFilename().c_str(), vector3df(0,0,0), vector3df(0,0,0), props.getScale())
{
	mesh->setParent(parent);
}

Turret::~Turret()
{
}
