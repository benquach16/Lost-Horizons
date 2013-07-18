#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include <string>
#include <vector>

#include "object.h"
#include "turret.h"
#include "item.h"
#include "shipproperties.h"
#include "objectmanager.h"

//for finite state machine implementation
enum E_AI_STATES
{
	STATE_PATROLLING,
	STATE_FLEEING,
	STATE_ATTACKING,
	STATE_DEFENDING,
	STATE_ASSAULTING
};

//each ship has several subsystems
struct Subsystem
{
	int health;
	Subsystem() { health = 100; };
};

struct ShipInformation
{
	E_AI_STATES currentAIState;
	E_GAME_FACTIONS currentFaction;
	s32 hull, maxHull, armor, maxArmor, shield, maxShield, crew, maxCrew;
	f32 velocity, maxVelocity, maxTurn;
	vector3df targetRotation;
	ShipInformation() {}
	ShipInformation(const ShipProperties &props)
		: currentAIState(STATE_PATROLLING), hull(props.getHull()), maxHull(hull), velocity(0.f),
		  maxVelocity(props.getMaxVel()), maxTurn((f32)props.getMaxTurn()) {}
};

//basic ship class
class Ship : public Object
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

	Ship();
	Ship(const vector3df &position, const vector3df &rotation, bool isPlayer, const ShipProperties &props);
	Ship(const vector3df &position, const vector3df &rotation, bool isPlayer, const ShipProperties &props, const ShipInformation &info);
	//copy constructor
	Ship(const Ship *s);
	//overloaded assignment operator
	Ship& operator=(const Ship *s);
	virtual ~Ship();
	bool getIsPlayer();

	virtual void run(f32 frameDeltaTime);

	void increaseVelocity(f32 frameDeltaTime);
	void decreaseVelocity(f32 frameDeltaTime);

	//rotate ship to specific angle
	void setTargetRotationTo(const vector3df &newTargetRotation);
	const vector3df &getTargetRotation() const;

	//target functions
	void setTarget(Ship *newTarget);
	void removeTarget();

	//equip funcs
	void setMediumTurret(const TurretProperties& props, int slot);

	const ShipInformation& getShipInfo() const;

	//some accessors
	const int& getMaxArmor() const;
	const int& getMaxShield() const;

protected:
	//protected functions
	void rotate(f32 frameDeltaTime);
	void movement(f32 frameDeltaTime);
	void initTurrets();
	void aimTurrets(f32 frameDeltaTime);

	bool isPlayer;
	//iterator to 'this'
	std::list<Ship*>::iterator it;

	//stats
	//basic ship type
	ShipProperties props;
	ShipInformation info;

	//data containers for the turrets of the ship
	std::vector<TurretSlot*> heavyTurrets;
	std::vector<TurretSlot*> mediumTurrets;
	std::vector<TurretSlot*> lightTurrets;

	//important misc variables
	Ship *shipTarget;

	//inventory of ship
	
	
};
#endif
