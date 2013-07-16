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
	ShipInformation(E_AI_STATES currentAIState, s32 hull, s32 maxHull, f32 velocity, f32 maxVelocity, f32 maxTurn)
		: currentAIState(currentAIState), hull(hull), maxHull(maxHull), velocity(velocity), maxVelocity(maxVelocity),
		  maxTurn(maxTurn) {}
};

//basic ship class
class Ship : public Object
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

	Ship();
	Ship(const ShipProperties &props, const vector3df &position, const vector3df &rotation, bool isPlayer);
	//copy constructor
	Ship(const Ship *s);
	//overloaded assignment operator
	Ship& operator=(const Ship *s);
	virtual ~Ship();
	//for deleting non player ships easily
	void removeAI();

	virtual void run(f32 frameDeltaTime);

	void increaseVelocity(f32 frameDeltaTime);
	void decreaseVelocity(f32 frameDeltaTime);

	//rotate ship to specific angle
	void setTargetRotationTo(const vector3df &newTargetRotation);
	const vector3df &getTargetRotation() const;

	//equip funcs
	void setMediumTurret(const TurretProperties& props, int slot);

	const ShipInformation& getShipInfo() const;

protected:
	//protected functions
	void rotate(f32 frameDeltaTime);
	void movement(f32 frameDeltaTime);
	void initTurrets();

	bool isPlayer;
	//iterator to 'this'
	std::list<Ship*>::iterator it;

	//stats
	//basic ship type
	ShipProperties props;
	ShipInformation info;

	//data containers for the turrets of the ship
	std::vector<TurretSlot*> mediumTurrets;

	//important misc variables
	Ship *shipTarget;

	//inventory of ship
	
};
#endif
