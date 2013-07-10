#include "turret.h"

TurretSlot::TurretSlot() : joint(0), childTurret(0)
{
	//default constructor
}

TurretSlot::TurretSlot(irr::IrrlichtDevice *graphics, const turretInformation &properties, IBoneSceneNode *joint) : joint(joint), childTurret(0),
	properties(properties), rotationOffset(properties.rotation), graphics(graphics)
{
	joint->setRotation(rotationOffset);
}

void TurretSlot::assignTurret(const TurretProperties &props)
{
	removeTurret();
	childTurret = new Turret(graphics, props, joint);
}

void TurretSlot::removeTurret()
{
	if(childTurret)
		delete childTurret;
	childTurret=0;
}


//BEGIN TURRET
Turret::Turret()
{
	//default constructor
}

Turret::Turret(irr::IrrlichtDevice *graphics, const TurretProperties &props, IBoneSceneNode *joint) : 
	Object(graphics, props.getFilename().c_str(), vector3df(0,0,0), vector3df(0,0,0), props.getScale())
{
	mesh->setParent(joint);
}

Turret::~Turret()
{
}
