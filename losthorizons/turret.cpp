#include "turret.h"

Turret::Turret()
{
	//default constructor
}

Turret::Turret(irr::IrrlichtDevice *graphics, const TurretProperties &props, IBoneSceneNode *joint) : 
	Object(graphics, props.getFilename().c_str(), vector3df(0,0,0), vector3df(0,0,0), props.getScale())
{
	joint->addChild(mesh);
}

Turret::~Turret()
{
}
