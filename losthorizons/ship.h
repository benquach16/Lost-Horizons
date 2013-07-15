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

struct ShipData
{
	s32 hull, armor, shield, maxHull, maxArmor, maxShield, crew, maxCrew;
	f32 velocity, maxVelocity, maxTurn;
	vector3df position, rotation, targetRotation;
	//std::vector<TurretData> mediumTurrets;
	E_AI_STATES currentAIState;
	E_GAME_FACTIONS currentFaction;
	//u32 shipTarget;
};

//basic ship class
class Ship : public Object
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

	Ship();
	Ship(const ShipProperties &props,
		const vector3df &position, const vector3df &rotation, bool isPlayer);
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

	ShipData getShipData();

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
	int hull, armor, shield;
	int maxHull, maxArmor, maxShield;

	f32 velocity;
	f32 maxVelocity;
	f32 maxTurn;
	int crew;
	int maxCrew;

	//data containers for the turrets of the ship
	std::vector<TurretSlot*> mediumTurrets;

	//for that big ship feel
	vector3df targetRotation;

	//important misc variables
	E_AI_STATES currentAIState;
	E_GAME_FACTIONS currentFaction;
	Ship *shipTarget;
	//inventory of ship
	
	
};
#endif
