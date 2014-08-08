#include "stdafx.h"
#include "globals.h"
#include "missile.h"

using namespace base;

Missile::Missile(const u16 ID, const TargetableObject *target, const TurretProperties &turretProps, 
		const vector3df &position, 
		const vector3df &rotation) : 
Projectile(ID, turretProps,
		   position,
		   rotation),
		   target(target)
{

}

Missile::~Missile()
{

}

bool Missile::run()
{
	//fly torwards the target
	//but not liike too fast you know
	vector3df targetRotation = target->getPosition() - getPosition();
	targetRotation = targetRotation.getHorizontalAngle();
	setRotation(targetRotation);
	return Projectile::run();
}
