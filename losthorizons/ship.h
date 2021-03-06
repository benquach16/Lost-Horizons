#ifndef _SHIP_H_
#define _SHIP_H_

#include "targetableobject.h"
#include "turret.h"
#include "shipproperties.h"
#include "objectmanager.h"
#include "projectile.h"
#include "cargo.h"
#include "fighter.h"
#include "fleet.h"

//for finite state machine implementation
enum E_AI_STATE
{
	AI_PATROLLING,
	AI_FLEEING,
	AI_ATTACKING,
	AI_DEFENDING,
	AI_ASSAULTING,
	AI_TRADING,
	AI_FOLLOWING,
	AI_DOORDER
};

//this is different than states cause each ship is meant to do something specific
//combat, trading, mining, etc
enum E_AI_ROLE
{
	SHIP_MINER,
	SHIP_TRADER,
	SHIP_COMBAT,
	SHIP_ESCORT
};

//we have to be able to give commands to our slave ships
//maybe make struct?
enum E_AI_ORDER
{
	ORDER_NULL,
	ORDER_MOVETOLOCATION,
	ORDER_ATTACKGENERAL,
	ORDER_ATTACKTARGET,
	ORDER_ATTACKANDMOVE,
	ORDER_FOLLOW,
	ORDER_FOLLOW_PASSIVE,
	ORDER_COUNT
};

enum E_SUBSYSTEM_TYPE
{
	SUBSYSTEM_BRIDGE,
	SUBSYSTEM_DECK1,
	SUBSYSTEM_DECK2,
	SUBSYSTEM_ELEVATOR,
	SUBSYSTEM_ENGINE,
	SUBSYSTEM_WARPDRIVE,
	SUBSYSTEM_SHIELD,
	SUBSYSTEM_POWERPLANT,
	SUBSYSTEM_HEAVYWEAPONS,
	SUBSYSTEM_MEDIUMWEAPONS,
	SUBSYSTEM_LIGHTWEAPONS,
	SUBSYSTEM_POINTDEFENSE,
	//number of subsystems
	SUBSYSTEM_COUNT
};

enum E_SHIELD_DIRECTIONS
{
	SHIELD_NULL,
	SHIELD_PORT,
	SHIELD_STARBOARD,
	SHIELD_FORE,
	SHIELD_AFT //ships shouldnt really have this except for very very speicific ones
};



//store all the ship info in a struct so we can save it easily
struct ShipInformation
{
	ObjectManager::E_SHIP_LIST shipType;
	E_GAME_FACTION currentFaction;
	E_AI_STATE currentAIState;
	E_AI_ROLE currentAIRole;
	E_AI_ORDER currentAIOrder;
	s32 hull, maxHull, armor, maxArmor, shield, maxShield, energy, maxEnergy, crew, maxCrew, fighters, maxFighters;
	f32 velocity, maxVelocity, maxTurn;
	vector3df targetRotation;
	vector3df orderMove;
	bool docked, warping;
	//directional shielding
	E_SHIELD_DIRECTIONS shieldDirection;
	ShipInformation() {}
	//do something later about this autistic block of code
	ShipInformation(ObjectManager::E_SHIP_LIST shipType, E_GAME_FACTION faction)
		: shipType(shipType), currentFaction(faction), currentAIState(AI_PATROLLING), currentAIOrder(ORDER_NULL),
		  hull(ObjectManager::shipList[shipType]->getMaxHull()), maxHull(hull),
		  armor(ObjectManager::shipList[shipType]->getMaxArmor()), maxArmor(armor),
		  shield(ObjectManager::shipList[shipType]->getMaxShield()), maxShield(shield),
		  energy(ObjectManager::shipList[shipType]->getMaxEnergy()), maxEnergy(energy),
		  fighters(ObjectManager::shipList[shipType]->getMaxFighters()), maxFighters(fighters),
		  crew(ObjectManager::shipList[shipType]->getMaxCrew()), maxCrew(crew),
		  velocity(0.f), maxVelocity(ObjectManager::shipList[shipType]->getMaxVel()),
		  maxTurn((f32)ObjectManager::shipList[shipType]->getMaxTurn()),
		  targetRotation(vector3df()), docked(false), warping(false),
		  shieldDirection(SHIELD_NULL)
	{}
};

//basic ship class
class Ship : public TargetableObject
{
public:
	//contain the list inside ship class so all ships can access any other ship if needed
	static std::vector<Ship*> allShips;
	//use this to pull names of the subsystem
	static wchar_t *subsystemNames[SUBSYSTEM_COUNT];
	//this is mostly for use by other classes but keep it in ship for conciseness
	static wchar_t *orderNames[ORDER_COUNT];

	Ship(const E_GAME_FACTION& faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Ship(const u16 ID, const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation);
	Ship(const Ship *s, const vector3df &position, const vector3df &rotation);
	Ship& operator=(const Ship *s);
	virtual ~Ship();
	virtual bool run();

	//changes ship's velocity
	void increaseVelocity();
	void decreaseVelocity();

	//combat functions
	//this fires all turrets
	void fireTurrets();


	void damage(int damage);
	//overloaded to grab the position of the projectile as it hits the ship
	//this is mainly for directional shielding
	void damage(int damage, const vector3df& projectilePosition);
	//does exactly what it says
	void modifyEnergy(int modifier);
	//rotate ship to specific angle
	void setTargetRotation(const vector3df &newTargetRotation);
	const vector3df& getTargetRotation() const;

	//target functions
	void setTarget(TargetableObject *newTarget);

	//equip funcs
	void setHeavyTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot);
	void setMediumTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot);
	void setLightTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot);
	void setPDTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot);
	void setShieldDirection(const E_SHIELD_DIRECTIONS direction);

	//forgot what this function did
	void repairShip();

	//some setters
	void setFaction(E_GAME_FACTION currentFaction);
	

	//some accessors
	const ShipInformation& getInfo() const;
	const TargetableObject* getShipTarget() const;
	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	s8 *getSubsystems();
	Inventory& getInventory();
	std::vector<TurretSlot*>& getTurrets(E_TURRET_CLASS turretClass);
	std::vector<vector2d<s32> > getHeavyTurretEquipPosition();
	std::vector<vector2d<s32> > getMediumTurretEquipPosition();
	std::vector<vector2d<s32> > getLightTurretEquipPosition();


	//returns whether the ship is a player or AI
	bool isPlayer() const;

	//docking functions
	void dockWithTarget();
	void undockWithTarget();

	//launch fighters
	void launchFighters();
	
	void warpToTarget();

	//some misc functions
	//fleet functions
	void addToFleet(Fleet *f);
	void removeFromFleet();
	void setShipRole(const E_AI_ROLE newRole);
	const E_AI_ROLE getShipRole() const;
	void giveShipOrder(const E_AI_ORDER newOrder, vector3df &newPosition);
	void giveOrderMove(const vector3df &position);
	void giveOrderAttackGeneral(const vector3df& position);
	void giveOrderAttackTarget(TargetableObject* newTarget);
	void giveOrderAttackAndMove(const vector3df& position);
	void giveOrderFollow();
	void giveOrderFollowPassive();
	void removeOrder();

	const E_AI_ORDER getShipOrder() const;
	//realized we needed this or else no ships would ever be added to another ones fleet
	Fleet *getFleet();
	void highlightShip();

protected:
	//ship stats
	ShipInformation info;

	//data containers
	s8 subsystems[SUBSYSTEM_COUNT];
	Inventory inventory;
	//turrets
	std::vector<TurretSlot*> heavyTurrets;
	std::vector<TurretSlot*> mediumTurrets;
	std::vector<TurretSlot*> lightTurrets;
	std::vector<TurretSlot*> pdTurrets;
	
	//fighters
	//i dont understand why this breaks everything
	//std::vector<Fighter*> launchedFighters;

	//important misc variables
	TargetableObject *shipTarget;

	//engine trail variables
	std::vector<scene::IParticleSystemSceneNode*> engineParticles;
	std::vector<scene::IBillboardSceneNode*> coronaEffects;

	//change the ship's position
	void rotate();
	void movement();
	//function allows ship to do accuracy prediction
	//important for targets more than 5 feet away!
	vector3df getAlteredShipPosition() const;
	void drawShields();

	//fleet that the ship is attached to, if any
	Fleet *shipFleet;
	scene::ISceneNode *shield;

private:
	//turret functions
	void initTurrets();
	void aimTurrets();
	void aimPointDefense();
	//initialize particle effects
	void initEngineTrails();

	//AI functions
	void runAI();
	void doOrderSM();
	//because shit attacks alot
	void runAttacking();
	void updateStates();
	void searchForTarget();
	void searchForFriendlyStation();
	void setCorrectShieldAngle();
	void setCorrectShieldAngle(const vector3df &targetRotation);	//for optimization reaasons we don't calculate this twice

	//controls how fast we want the shields to recharge
	u32 shieldTimer;
	//seperate timer for energy recharge
	u32 energyTimer;
	u32 energyRechargeTimer;

	//timekeeping variables
	u32 currentTime;
	u32 fighterLaunchTime;
	u32 fighterDamageTime;
	u32 fighterUpdateTime;

	//some ai variables to make them super l33t
	//we named this should fire, because it can fire, but that doesnt mean it should
	bool shouldFire;

	//iterator to this
	unsigned index;
};
#endif
