#ifndef _TURRET_H_
#define _TURRET_H_

#include "object.h"
#include "objectmanager.h"
#include "turretproperties.h"
#include "shipproperties.h"

class Turret;

//ships get this assigned to their joints so we can do turret firing arcs
class TurretSlot
{
public:
	TurretSlot();
	TurretSlot(const turretInformation &properties, IBoneSceneNode *joint);
	void assignTurret(const TurretProperties &props);
	void removeTurret();
	//to see which direction the turret arc is facing and covers
	//good for debug purposes and players
	void drawArc();
	~TurretSlot();

protected:
	irr::IrrlichtDevice *graphics;
	ISceneNode *offset;
	IBoneSceneNode *joint;
	Turret *childTurret;
	turretInformation properties;
	vector3df rotationOffset;
};

//Each turret needs a 'base' and a 'gun'
//in order to act properly
class TurretGun
{
public:

};

class Turret : public Object
{
public:
	//default constructor
	Turret();
	//if you actually want to create a 3d model
	Turret(const TurretProperties &props, ISceneNode *parent);
	~Turret();

protected:
	TurretSlot *parentSlot;
};

#endif
