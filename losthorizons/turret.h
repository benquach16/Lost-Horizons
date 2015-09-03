#ifndef _TURRET_H_
#define _TURRET_H_

#include "object.h"
#include "objectmanager.h"
#include "turretproperties.h"
#include "shipproperties.h"
#include "projectile.h"
#include "missile.h"
#include "muzzleflash.h"

class Turret;
class Ship;

//ships get this assigned to their joints so we can do turret firing arcs
class TurretSlot
{
public:
	//constructors
	//parameterized constructor
	TurretSlot(const turretInformation &properties, scene::IBoneSceneNode *joint, const E_TURRET_CLASS turretClass, Ship* parent);
	//constructor for point defense oriented turretslots

	//assigns a turret to this slot
	void assignTurret(const ObjectManager::E_ITEM_LIST turretType);
	//just checks if this turret slot is filled
	bool getCanFire();
	bool fire();
	void removeTurret();
	//to see which direction the turret arc is facing and covers
	//good for debug purposes and players
	void drawArc();
	//actual aiming portion
	void aim(const core::vector3df &point);
	//make turret stop aiming
	void resetAim();
	void renderPosition();
	~TurretSlot();

	//used for projectile generation
	Ship* getParent() const;
	const core::vector3df& getCurrentAim() const;
	const core::vector3df& getPosition() const;
	const vector3df& getRelativePosition() const;
	const vector3df& getAbsolutePosition() const;
	const ObjectManager::E_ITEM_LIST getTurretType() const;

protected:
	//a dummy scene node to have the turret face in a particular direction
	scene::ISceneNode *offset;
	//another dummy scene node because joint absolute position seems to be completely fucked
	scene::ISceneNode *aimPoint;
	//pointer to the joint that we're parented to
	scene::IBoneSceneNode *joint;
	//pointer to the ship that this slot is parented to
	Ship *parent;
	//pointer to the turret model itself
	Turret *childTurret;
	//the stats for the current turret
	turretInformation properties;
	//the vector of the offset
	vector3df rotationOffset;
	//we store the direction in which the turret is aiming so we don't have to recalculate twice
	vector3df currentAim;
	//ensure target is shootable
	bool canFire;
	//we create a timer so that there is a fire rate
	int shootTimer;
};

//turret model class
//deals with the actual rotation
class Turret : public Object
{
public:
	//default constructor
	Turret();
	//if you actually want to create a 3d model
	Turret(const ObjectManager::E_ITEM_LIST turretType, scene::ISceneNode *parent, TurretSlot *parentSlot);
	~Turret();

	virtual bool run();
	void aim(const core::vector3df &rotation);
	void fire(const vector3df &rotation);

	const Ship* getParent() const;
	const ObjectManager::E_ITEM_LIST getTurretType() const
	{
		return turretType;
	}

protected:
	TurretSlot *parentSlot;
	const ObjectManager::E_ITEM_LIST turretType;
	int shootTimer;
	//pointer to joint that our fire position is
	scene::IBoneSceneNode *shootJoint;
};

#endif
