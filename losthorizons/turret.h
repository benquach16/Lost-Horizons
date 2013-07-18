#ifndef _TURRET_H_
#define _TURRET_H_

#include "object.h"
#include "objectmanager.h"
#include "turretproperties.h"
#include "shipproperties.h"

class Turret;
class Ship;

//ships get this assigned to their joints so we can do turret firing arcs
class TurretSlot
{
public:
	TurretSlot();
	TurretSlot(const turretInformation &properties, IBoneSceneNode *joint, const E_TURRET_CLASS &turretClass, Ship* parent);
	void assignTurret(const TurretProperties &props);
	void removeTurret();
	//to see which direction the turret arc is facing and covers
	//good for debug purposes and players
	void drawArc();
	//actual aiming portion
	void aim(const core::vector3df &point, f32 frameDeltaTime);
	~TurretSlot();

protected:
	ISceneNode *offset;
	IBoneSceneNode *joint;
	Ship *parent;
	Turret *childTurret;
	turretInformation properties;
	vector3df rotationOffset;
};


class Turret : public Object
{
public:
	//default constructor
	Turret();
	//if you actually want to create a 3d model
	Turret(const TurretProperties &props, ISceneNode *parent);
	void aim(const core::vector3df &rotation, float frameDeltaTime);

	~Turret();

protected:
	TurretSlot *parentSlot;
	TurretProperties props;
};

#endif
