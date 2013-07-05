#ifndef _TURRET_H_
#define _TURRET_H_

#include "object.h"
#include "turretproperties.h"
//Each turret needs a 'base' and a 'gun'
//in order to act properly
class TurretBase
{
};

class TurretGun
{
};

class Turret : public Object
{
public:
	//default constructor
	Turret();
	//if you actually want to create a 3d model
	Turret(irr::IrrlichtDevice *graphics, const TurretProperties &props, IBoneSceneNode *joint);
	~Turret();

protected:

};

#endif
