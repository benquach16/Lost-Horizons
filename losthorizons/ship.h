#ifndef _SHIP_H_
#define _SHIP_H_

#include <list>
#include <string>
#include <vector>

#include "object.h"
#include "targetableobject.h"
#include "turret.h"
#include "item.h"
#include "shipproperties.h"
#include "objectmanager.h"
#include "projectile.h"
#include "explosion.h"
#include "inventory.h"
#include "cargo.h"
#include "fighter.h"

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
	std::wstring name;
	Subsystem() { health = 100; };
};

//store all the ship info in a struct so we can save it easily
struct ShipInformation
{
	ObjectManager::E_SHIP_LIST shipType;
	E_GAME_FACTIONS currentFaction;
	E_AI_STATES currentAIState;
	s32 hull, maxHull, armor, maxArmor, shield, maxShield, energy, maxEnergy, crew, maxCrew, fighters, maxFighters;
	f32 velocity, maxVelocity, maxTurn;
	vector3df targetRotation;
	bool docked;
	bool warping;
	Inventory inventory;
	ShipInformation() {}
	ShipInformation(ObjectManager::E_SHIP_LIST shipType, E_GAME_FACTIONS faction)
		: shipType(shipType), currentFaction(faction), currentAIState(STATE_PATROLLING),
		  hull(ObjectManager::shipList[shipType].getMaxHull()), maxHull(hull),
		  armor(ObjectManager::shipList[shipType].getMaxArmor()), maxArmor(armor),
		  shield(ObjectManager::shipList[shipType].getMaxShield()), maxShield(shield),
		  energy(ObjectManager::shipList[shipType].getMaxEnergy()), maxEnergy(energy),
		  fighters(ObjectManager::shipList[shipType].getMaxFighters()), maxFighters(fighters),
		  crew(1), maxCrew(ObjectManager::shipList[shipType].getMaxCrew()),
		  velocity(0.f), maxVelocity(ObjectManager::shipList[shipType].getMaxVel()),
		  maxTurn((f32)ObjectManager::shipList[shipType].getMaxTurn()),
		  targetRotation(vector3df(0.f,0.f,0.f)), docked(false), warping(false){}
};

//basic ship class
class Ship : public TargetableObject
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::list<Ship*> allShips;

	Ship(const E_GAME_FACTIONS& faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Ship(u32 ID, const ShipInformation &info, const vector3df &position, const vector3df &rotation);
	Ship(const Ship *s, const vector3df &position, const vector3df &rotation);
	Ship& operator=(const Ship *s);
	virtual ~Ship();
	virtual void run(f32 frameDeltaTime);

	//changes ship's velocity
	void increaseVelocity(f32 frameDeltaTime);
	void decreaseVelocity(f32 frameDeltaTime);

	//combat functions
	void fireTurrets();
	void damage(int val);

	//rotate ship to specific angle
	void setTargetRotation(const vector3df &newTargetRotation);
	const vector3df& getTargetRotation() const;

	//target functions
	void setTarget(TargetableObject *newTarget);
	void removeTarget();

	//equip funcs
	void setHeavyTurret(const TurretProperties& props, unsigned slot);
	void setMediumTurret(const TurretProperties& props, unsigned slot);
	void setLightTurret(const TurretProperties& props, unsigned slot);
	void setPDTurret(const TurretProperties& props, unsigned slot);

	//some setters
	void setFaction(E_GAME_FACTIONS currentFaction);

	//some accessors
	const ShipInformation& getInfo() const;
	const TargetableObject* getShipTarget() const;
	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	//returns an lvalue
	Inventory& getInventory();
	//returns an rvalue
	const Inventory& getInventory() const;

	//returns whether the ship is a player or AI
	bool isPlayer() const;
	//function to remove this ship from all targets
	//useful for segfaults and electronic warfare
	void removeThisFromTargets();

	//docking functions
	void dockWithTarget();
	void undockWithTarget();

	//launch fighters
	void launchFighters();
	
	void warpToTarget();
protected:
	//ship stats
	ShipInformation info;

	//data containers for the turrets of the ship
	std::vector<TurretSlot*> heavyTurrets;
	std::vector<TurretSlot*> mediumTurrets;
	std::vector<TurretSlot*> lightTurrets;
	std::vector<TurretSlot*> pdTurrets;

	//data container for ship subsystems
	std::vector<Subsystem> subsystems;

	//important misc variables
	TargetableObject *shipTarget;
	//engine trail variables
	std::vector<IParticleSystemSceneNode*> engineParticles;
	std::vector<IBillboardSceneNode*> coronaEffects;
	
	//iterator to 'this'
	std::list<Ship*>::iterator it;

	//controls how fast we want the shields to recharge
	unsigned shieldTimer;

private:
	
	//change the ship's position
	void rotate(f32 frameDeltaTime);
	void movement(f32 frameDeltaTime);

	//turret functions
	void initTurrets();
	void aimTurrets(f32 frameDeltaTime);

	//initialize particle effects
	void initEngineTrails();

	//AI functions
	void runAI();
	void updateStates();
	void searchForTarget();

	//timekeeping variables
	u32 currentTime;
	u32 fighterLaunchTime;
	u32 fighterDamageTime;
};
#endif
