#include "stdafx.h"
#include "ship.h"
#include "globals.h"
#include <iostream>
#pragma hdrstop

using namespace base;

//set up static elements
std::vector<Ship*> Ship::allShips;
//TODO: start putting stuff like this in an xml file
wchar_t *Ship::subsystemNames[] = { L"Bridge", L"Deck 1", L"Deck 2", L"Elevator",
	L"Engine", L"Warp Drive", L"Shield Generator", L"Power Plant",
	L"Heavy Weapons", L"Medium Weapons", L"Light Weapons", L"Point Defense"};

wchar_t *Ship::orderNames[] = { L"Waiting for orders", L"Moving to Location", L"Attacking",
	L"Attacking Target", L"Attacking Target and Moving",
	L"Following", L"Following and ignoring hostiles"};

//some globals for ship class
//time between ai updates to save cpu speed
const int AITIMER = 100;
const int ENERGYTIMER = 2500;
const int ENERGYTIMERSHIELD = 5000;
const int SHIELDTIMER = 15000;
const int FIGHTERDAMAGETIMER = 2520;

Ship::Ship(const E_GAME_FACTION &faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, *ObjectManager::shipList[shipType], position, rotation, faction), info(shipType, faction),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), energyTimer(0), energyRechargeTimer(0),
	  fighterDamageTime(0), fighterUpdateTime(0), index(allShips.size()), shipFleet(0), shouldFire(true)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;
	
	std::cout << '[' << ID << "]Ship object created" << std::endl;

	//add it to the ships list
	allShips.push_back(this);
	
	for (unsigned i = 0; i < SUBSYSTEM_COUNT; ++i) {
		subsystems[i] = 100;
	}

	//set up the ship turrets
	initTurrets();
	initEngineTrails();

	setNormalMap(vdriver->getTexture(ObjectManager::shipList[shipType]->getNormalMap()));
	setMediumTurret(ObjectManager::E_ITEM_LIST::HYDRAI,3);
	setMediumTurret(ObjectManager::E_ITEM_LIST::HYDRAI,2);
	setMediumTurret(ObjectManager::E_ITEM_LIST::HYDRAI,1);
	setMediumTurret(ObjectManager::E_ITEM_LIST::HYDRAI,0);
	setLightTurret(ObjectManager::E_ITEM_LIST::ANTIMATTERI,0);
	setLightTurret(ObjectManager::E_ITEM_LIST::ANTIMATTERI,1);
	setLightTurret(ObjectManager::E_ITEM_LIST::ANTIMATTERI,2);
	setLightTurret(ObjectManager::E_ITEM_LIST::ANTIMATTERI,3);
	setPDTurret(ObjectManager::E_ITEM_LIST::GATLINGI, 0);
	setPDTurret(ObjectManager::E_ITEM_LIST::GATLINGI, 1);
	setPDTurret(ObjectManager::E_ITEM_LIST::GATLINGI, 2);
	setPDTurret(ObjectManager::E_ITEM_LIST::GATLINGI, 3);
	inventory.addItem(ObjectManager::E_ITEM_LIST::WATER, 100);
	inventory.addItem(ObjectManager::E_ITEM_LIST::PHOTONI, 4);

	//artificially force neutral ships to be traders right now
	//this should be TEMPORARY
	//need to add in stuff like ship roles!!!!!!
	//Redundant. can just use setRole function now
	/*
	if(faction == FACTION_NEUTRAL)
		info.currentAIState = AI_TRADING;*/
	info.armor = 999999;
	shield = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/shield.x"), 0, -1, getPosition());
	shield->setMaterialFlag(video::EMF_LIGHTING, false);
	shield->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

Ship::Ship(const u16 ID, const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation)
	: TargetableObject(ID, *ObjectManager::shipList[info.shipType], position, rotation, info.currentFaction), info(info),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), fighterDamageTime(0), energyTimer(0), energyRechargeTimer(0),
	  fighterUpdateTime(0), index(allShips.size()), shipFleet(0), shouldFire(true)
{
	//add it to the ships list
	allShips.push_back(this);

	std::cout << '[' << ID << "]Ship object created" << std::endl;

	for (unsigned i = 0; i < SUBSYSTEM_COUNT; ++i) {
		this->subsystems[i] = subsystems[i];
	}

	//set up the ship turrets
	initTurrets();
	initEngineTrails();
	
	shield = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/shield.x"), 0, -1, getPosition());
	shield->setMaterialFlag(video::EMF_LIGHTING, false);
	shield->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

//copy constructor
Ship::Ship(const Ship *s, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, *ObjectManager::shipList[s->info.shipType], position, rotation, s->faction), info(s->info),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), fighterDamageTime(0), energyTimer(0), energyRechargeTimer(0),
	  fighterUpdateTime(0), index(allShips.size()), shipFleet(0), shouldFire(true)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Ship object created" << std::endl;

	//add it to the ships list
	allShips.push_back(this);

	for (unsigned i = 0; i < SUBSYSTEM_COUNT; ++i) 
	{
		subsystems[i] = s->subsystems[i];
	}

	initTurrets();
	initEngineTrails();
}

//assignmennt operator
Ship& Ship::operator=(const Ship *s)
{
	if (s && this != s)
	{
		//TODO: ASSISNGMENT OPERATOR!!!
		changeMesh(s->filename.c_str());
		info = s->info;
		for(unsigned i = 0; i < heavyTurrets.size(); i++)
		{
				delete heavyTurrets[i];
		}
		for(unsigned i = 0; i < mediumTurrets.size(); i++)
		{
				delete mediumTurrets[i];
		}
		for(unsigned i = 0; i < lightTurrets.size(); i++)
		{
				delete lightTurrets[i];
		}
		//after we clear make sure we create
		for(unsigned i = 0; i < s->heavyTurrets.size(); i++)
		{
			
		}
	}
	return *this;
}

Ship::~Ship()
{
	//clear memory we allocated
	for (unsigned i = 0; i < heavyTurrets.size(); ++i)
		delete heavyTurrets[i];
	for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		delete mediumTurrets[i];
	for (unsigned i = 0; i < lightTurrets.size(); ++i)
		delete lightTurrets[i];
	for (unsigned i = 0; i < pdTurrets.size(); ++i)
		delete pdTurrets[i];
	while (!engineParticles.empty())
	{
		engineParticles.back()->remove();
		engineParticles.pop_back();
	}
	while (!coronaEffects.empty())
	{
		coronaEffects.back()->remove();
		coronaEffects.pop_back();
	}
	shield->remove();
	allShips[index] = allShips.back();
	allShips[index]->index = index;
	allShips.pop_back();
	if(shipFleet)
	{
		//make sure the fleet doesnt hold old pointers
		shipFleet->removeShipFromFleet(this);
		shipFleet = 0;
	}
}

bool Ship::run()
{
	if (info.hull > 0)
	{
		if (!info.docked)
		{
			//make sure its alive to do anything
			//if the crew is 0 the ship is effectively dead
			//make it rotate to its targetted rotation first
			//and movement
			rotate();
			aimTurrets();
			drawShields();
			if (shipTarget && !shipTarget->getActive())
			{
				//remove
				shipTarget = 0;
			}
			if (info.warping)
			{
				//ok so we're warping
				//check if we're aligned to the target
				if (!(getRotation().Y - 3 > getTargetRotation().Y || getRotation().Y + 3 < getTargetRotation().Y ||
					getRotation().X - 3 > getTargetRotation().X || getRotation().X + 3 < getTargetRotation().X))
				{
					if (info.velocity < 500)
					{
						info.velocity += (5+abs(info.velocity)/2)*frameDeltaTime;
					}
					if (getPosition().getDistanceFrom(shipTarget->getPosition()) < 10000)
					{
						info.warping = false;
						info.velocity = 0;
					}
				}
			}

			movement();

			//recharge shields
			if(info.energy < info.maxEnergy && energyTimer < timer->getTime() && energyRechargeTimer < timer->getTime())
			{
				//piggyback off the shield recharge timer
				info.energy += 5;
				energyTimer = timer->getTime() + 50;
			}
			if (subsystems[SUBSYSTEM_SHIELD] > 0 && info.shield < info.maxShield && shieldTimer < timer->getTime())
			{
				info.shield++;
				shieldTimer  = timer->getTime() + 100;
			}
			

			//if is not player do ai stuff
			if (!isPlayer())
			{
				runAI();
			}
		}
	}
	else
	{
		//we have to delete this ship when it asplodes
		//so create an explosion and delete itself
		Explosion *e = new Explosion(getPosition());
		//lets create some loot to drop
		Cargo *loot = new Cargo(getPosition(), true);
		remove();
	}
	return TargetableObject::run();
}

//increases velocity based on how fast the ship is going
void Ship::increaseVelocity()
{
	if (info.velocity < info.maxVelocity)
		info.velocity += (10+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::decreaseVelocity()
{
	if (info.velocity > -info.maxVelocity)
		info.velocity -= (10+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::fireTurrets()
{
	//lets do this in a way that doesn't involve middlemen
	//later just call each of the fire functions
	if(info.energy > 0)
	{
		energyRechargeTimer = timer->getTime() + ENERGYTIMER;
		for (unsigned i = 0; i < mediumTurrets.size(); ++i) 
		{
			mediumTurrets[i]->fire();
		}
		for (unsigned i = 0; i < lightTurrets.size(); ++i)
		{
			lightTurrets[i]->fire();
		}
	}
}


void Ship::damage(int damage)
{
	//do damage stuff here
	//check shields, then armor then hull

	if (info.armor > 0)
	{
		info.armor -= damage;
	}
	else
	{
		//damage hull
		info.hull -= damage;
		//since armor and hull are damaged, kill off some of the crew
		info.crew -= (rand()%info.crew)/4;
		//and damage a subsystem
		int i = rand()%SUBSYSTEM_COUNT;
		if(subsystems[i] > 0)
			subsystems[i] -= rand()%100;
	}
}

void Ship::damage(int damage, const vector3df& projectilePosition)
{
	//check this first to increase performance
	if(info.shield > 0)
	{
		//bigger damage function to take into account shield rotation
		//calculate the angle so we can see if it hit the shield or not
		//we only do x and z because y is only a formality in this game
		float x = projectilePosition.Z - getPosition().Z;
		float z = projectilePosition.X - getPosition().X;
		//do math here
		float angle = std::atan2(x,z) * (180.f/PI);
		angle += getRotation().Y;
		if(angle > 360)
			angle -= 360;
		if(angle < 1)
			angle += 360;
		//std::cout << angle;
		if(angle > 45 && angle < 135)
		{
			//std::cout << "front" << std::endl;
			if(info.shieldDirection == SHIELD_FORE)
			{
				//damage the shields
				info.shield -= damage;
			}
			else
				this->damage(damage);
		}
		else if(angle > 135 && angle < 225)
		{
			//std::cout << "left" << std::endl;	
			if(info.shieldDirection == SHIELD_PORT)
			{
				info.shield -= damage;
			}
			else
				this->damage(damage);
		}
		else if(angle > 225 && angle < 315)
		{
			//std::cout << "back" << std::endl;
			if(info.shieldDirection == SHIELD_AFT)
			{
				info.shield -= damage;
			}
			else
				this->damage(damage);
		}
		else
		{
			//std::cout << "right" << std::endl;
			if(info.shieldDirection == SHIELD_STARBOARD)
			{
				info.shield -= damage;
			}
			else
				this->damage(damage);
		}
	}
	else
		this->damage(damage);
}

void Ship::modifyEnergy(int modifier)
{
	if(info.energy > 0)
	{
		//just make sure we cant hit neg energy

		info.energy += modifier;
	}
}

void Ship::setTargetRotation(const vector3df &newTargetRotation)
{
	info.targetRotation = newTargetRotation;
	//if(info.targetRotation.Y > 360)
		//info.targetRotation.Y -= 360;
	//if(info.targetRotation.Y < -360)
		//info.targetRotation.Y += 360;
}

const vector3df &Ship::getTargetRotation() const
{
	return info.targetRotation;
}

void Ship::setTarget(TargetableObject *newTarget)
{
	shipTarget = newTarget;
}

//turret setter functions
void Ship::setMediumTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot)
{
	if (slot < mediumTurrets.size() && slot >= 0)
		mediumTurrets[slot]->assignTurret(turretType);
}

void Ship::setLightTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot)
{
	if (slot < lightTurrets.size() && slot >= 0)
		lightTurrets[slot]->assignTurret(turretType);
}

void Ship::setPDTurret(const ObjectManager::E_ITEM_LIST turretType, unsigned slot)
{
	if (slot < pdTurrets.size() && slot >= 0)
		pdTurrets[slot]->assignTurret(turretType);
}

void Ship::setShieldDirection(const E_SHIELD_DIRECTIONS direction)
{
	info.shieldDirection = direction;
}

void Ship::repairShip()
{
	info.hull = info.maxHull;
	info.armor = info.maxArmor;
}

void Ship::setFaction(E_GAME_FACTION newFaction)
{
	info.currentFaction = newFaction;
}

const ShipInformation& Ship::getInfo() const
{
	return info;
}

const TargetableObject* Ship::getShipTarget() const
{
	return shipTarget;
}

const E_TARGETABLEOBJECT_TYPE Ship::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_SHIP;
}

s8 *Ship::getSubsystems()
{
	return subsystems;
}

Inventory& Ship::getInventory()
{
	return inventory;
}

std::vector<TurretSlot*>& Ship::getTurrets(E_TURRET_CLASS turretClass)
{
	if (turretClass == TURRET_HEAVY)
		return heavyTurrets;
	else if (turretClass == TURRET_MEDIUM)
		return mediumTurrets;
	else if (turretClass == TURRET_LIGHT)
		return lightTurrets;
	else
		return pdTurrets;
}

vector2d<s32> Ship::getHeavyTurretEquipPosition()
{
	//slow blocking function
	TurretSlot* tSlot = mediumTurrets[0];
	vector3df position = tSlot->getPosition();
	vector2d<s32> ret =  scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(position);
	ret.X-=16;
	ret.Y -=16;
	return ret;
}

bool Ship::isPlayer() const
{
	return ID == 0;
}

void Ship::dockWithTarget()
{
	//check if target is a spaec station

	if (getShipTarget() && getShipTarget()->getTargetableObjectType() == TARGETABLEOBJECT_SPACESTATION)
	{
		if (getShipTarget()->getPosition().getDistanceFrom(getPosition()) < 500)
		{
			info.docked = true;
			setPosition(getShipTarget()->getPosition());
		}
	}
}

void Ship::undockWithTarget()
{
	info.docked = false;
}

void Ship::launchFighters()
{
	if (info.fighters > 0)
	{
		if (fighterLaunchTime < timer->getTime())
		{
			//TODO MAKE DIFFERENT FIGHTERS AVAILABLE TO SHIPS
			Fighter *f = new Fighter(ObjectManager::E_FIGHTER_LIST::DRAGONFLY, 
			getPosition(), getRotation(), info.currentFaction, this);
			//launchedFighters.push_back(f);
			fighterLaunchTime = timer->getTime() + 500;
			info.fighters--;
		}
	
	}

}

void Ship::warpToTarget()
{

	if (shipTarget && subsystems[SUBSYSTEM_WARPDRIVE] > 0)
	{
		//make sure we have a target
		//save to variable first to avoid multiple sqrt operations
		const f32 dist = getPosition().getDistanceFrom(shipTarget->getPosition());

		if (dist > 10000)
		{
			//make sure we can't 'point jump' ship targets
			setTargetRotation((shipTarget->getPosition() - getPosition()).getHorizontalAngle());
			info.velocity = 0;
			info.warping = true;
		}
	}
	
}

void Ship::addToFleet(Fleet *f)
{
	//we set our shipfleet to this
	//should really only be used by the fleet class!!!
	shipFleet = f;
}

void Ship::removeFromFleet()
{
	shipFleet = 0;
}

void Ship::setShipRole(const E_AI_ROLE newRole)
{
	info.currentAIRole = newRole;

}

const E_AI_ROLE Ship::getShipRole() const
{
	return info.currentAIRole;
}

void Ship::giveShipOrder(const E_AI_ORDER newOrder, vector3df &newPosition)
{
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = newOrder;
	info.orderMove = newPosition;
}

void Ship::giveOrderMove(const vector3df& position)
{
	
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = ORDER_MOVETOLOCATION;
	info.orderMove = position;
}

void Ship::giveOrderAttackGeneral(const vector3df& position)
{
	
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = ORDER_ATTACKGENERAL;
	info.orderMove = position;
}

void Ship::giveOrderAttackTarget(TargetableObject* newTarget)
{
	shipTarget = newTarget;
	info.currentAIOrder = ORDER_ATTACKTARGET;
}

void Ship::giveOrderAttackAndMove(const vector3df& position)
{
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = ORDER_ATTACKANDMOVE;
	info.orderMove = position;
}

void Ship::giveOrderFollow()
{
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = ORDER_FOLLOW;
}

void Ship::giveOrderFollowPassive()
{
	
	info.currentAIState = AI_DOORDER;
	info.currentAIOrder = ORDER_FOLLOW_PASSIVE;
}

void Ship::removeOrder()
{
	info.currentAIState = AI_PATROLLING;
	info.currentAIOrder = ORDER_NULL;
}

Fleet* Ship::getFleet()
{
	return shipFleet;
}

void Ship::highlightShip()
{
	//lets try something that will work for sure
}

//all private functions go under here
//private function
//rotates ship to point
void Ship::rotate()
{
	vector3df currentRot = getRotation();
	//normalize targetrotation
	//change it so that we dont accidently rotate 360 degrees

	if (currentRot != info.targetRotation) 
	{
		
		if (currentRot.Y != info.targetRotation.Y) 
		{
			f32 slowY = currentRot.Z = 0.5f*abs(currentRot.Y - info.targetRotation.Y);

			if (slowY > info.maxTurn)
				slowY = info.maxTurn;
			if (currentRot.Z > 5)
				currentRot.Z = 5.f;
			//make sure we shorten the length of rotation
			//to avoid the 0 - 360 jump
			//std::cerr << currentRot.Y << " " << info.targetRotation.Y << std::endl;
			if(currentRot.Y > 270 && info.targetRotation.Y < 120)	
			{
				currentRot.Y += slowY*frameDeltaTime;
				currentRot.Z = -currentRot.Z;
				if(currentRot.Y > 360)
					currentRot.Y -= 360;
			}
			else if (currentRot.Y < 120 && info.targetRotation.Y > 270)	
			{
				currentRot.Y -= slowY*frameDeltaTime;
				currentRot.Z = -currentRot.Z;
				if(currentRot.Y < 0)
					currentRot.Y += 360;
			}
			else if (currentRot.Y < info.targetRotation.Y) 
			{
				//rotate right
				currentRot.Y += slowY*frameDeltaTime;
				currentRot.Z = -currentRot.Z;
			} 
			else
			{
				currentRot.Y -= slowY*frameDeltaTime;
			}
			
		}
		if (currentRot.X != info.targetRotation.X) {
			f32 slowX = 0.5f*abs(currentRot.X - info.targetRotation.X);
			if (slowX > info.maxTurn)
				slowX = info.maxTurn;
			//std::cerr << currentRot.X << " " << info.targetRotation.X << std::endl;
			if(currentRot.X > 270 && info.targetRotation.X < 90)	
			{
				currentRot.X += slowX*frameDeltaTime;
				if(currentRot.X > 360)
				{
					currentRot.X -= 360;
				}
			}
			else if (currentRot.X < 90 && info.targetRotation.X > 270)	
			{
				currentRot.X -= slowX*frameDeltaTime;
				if(currentRot.X < 0)
				{
					currentRot.X += 360;
				}
			}
			else if (currentRot.X > info.targetRotation.X) 
			{
				//rotate up
				//make sure we cant rotate past 70 up and down
				if(currentRot.X > -70)
					currentRot.X -= slowX*frameDeltaTime;
			}
			else 
			{
				//rotate down
				if(currentRot.X < 70)
					currentRot.X += slowX*frameDeltaTime;
			}
		}
		setRotation(currentRot);
	}
}

//private function
void Ship::movement()
{
	const f32 temp = frameDeltaTime*info.velocity;
	const f32 X = sin(getRotation().Y*PI/180)*temp + getPosition().X;
	const f32 Y = sin(-getRotation().X*PI/180)*temp + getPosition().Y;
	const f32 Z = cos(getRotation().Y*PI/180)*temp + getPosition().Z;

	//smooth out ship movement
	setPosition(getPosition()*0.2f + core::vector3df(X,Y,Z)*0.8f);
}

//protected function
vector3df Ship::getAlteredShipPosition() const
{
	//get the predicted position of the target ship
	vector3df ret(shipTarget->getPosition());
	if(shipTarget->getTargetableObjectType() == TARGETABLEOBJECT_SHIP)
	{
		float x = std::sin((shipTarget->getRotation().Y*PI)/180);
		float z = std::cos((shipTarget->getRotation().Y*PI)/180);
		float y = std::sin((shipTarget->getRotation().X*PI)/180);
		ret.X += x * ((Ship*)shipTarget)->getInfo().velocity *3;
		ret.Z += z * ((Ship*)shipTarget)->getInfo().velocity *3;
		ret.Y += y * ((Ship*)shipTarget)->getInfo().velocity *3;
	}
	return ret;
}

void Ship::drawShields()
{
	shield->setPosition(getPosition());
	//info.shieldDirection = SHIELD_FORE;
	switch (info.shieldDirection) {
	case SHIELD_FORE:
		shield->setRotation(getRotation());
		shield->setScale(vector3df(0.5,1,1));
		shield->setVisible(true);
		break;
	case SHIELD_PORT:
		shield->setRotation(getRotation() + vector3df(0,-90,0));
		shield->setScale(vector3df(1,1,0.5));
		shield->setVisible(true);
		break;
	case SHIELD_STARBOARD:
		shield->setRotation(getRotation() + vector3df(0, 90, 0));
		shield->setScale(vector3df(1,1,0.5));
		shield->setVisible(true);
		break;
	case SHIELD_AFT:
		shield->setRotation(getRotation() + vector3df(0, 180, 0));
		shield->setScale(vector3df(0.5, 1, 1));
		shield->setVisible(true);
		break;
	default:
		shield->setVisible(false);
		break;
	}
}

//private function
//initialises the turret slot classes for each ship
void Ship::initTurrets()
{
	//we create new turret slots and assign them to the ship
	for (int i = 0; i < ObjectManager::shipList[info.shipType]->getMaxHTurrets(); ++i)
	{
		//get the bone name and set it to the string
		std::string jointName("heavy_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType]->mediumTurrets[i], joint, TURRET_HEAVY, this);
		heavyTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType]->getMaxMTurrets(); ++i)
	{
		//get the bone name and set it to the string
		std::string jointName("turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType]->mediumTurrets[i], joint, TURRET_MEDIUM, this);
		mediumTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType]->getMaxLTurrets(); ++i)
	{
		std::string jointName("secondary_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType]->lightTurrets[i], joint, TURRET_LIGHT, this);
		lightTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType]->getMaxPTurrets(); ++i)
	{
		std::string jointName("light_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(turretInformation(), joint, TURRET_PD, this);
		pdTurrets.push_back(t);
	}
}

//private function
//aims turrets at current target
void Ship::aimTurrets()
{
	if (shipTarget)
	{
		//if has target
		for (unsigned i = 0; i < heavyTurrets.size(); i++)
		{
			heavyTurrets[i]->aim(shipTarget->getPosition());
		}
		for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		{
			//mediumTurrets[i]->aim(shipTarget->getPosition());
			mediumTurrets[i]->aim(getAlteredShipPosition());
		}
		for (unsigned i = 0; i < lightTurrets.size(); i++)
		{
			//lightTurrets[i]->aim(shipTarget->getPosition());
			lightTurrets[i]->aim(getAlteredShipPosition());
		}
	}
	else
	{
		//go back to aiming like normal
		for (unsigned i = 0; i < heavyTurrets.size(); ++i)
		{
			heavyTurrets[i]->resetAim();
		}
		for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		{
			mediumTurrets[i]->resetAim();
		}
		for (unsigned i = 0; i < lightTurrets.size(); ++i)
		{
			lightTurrets[i]->resetAim();
		}
	}

	aimPointDefense();

}

//private function
void Ship::aimPointDefense()
{
	bool missilesInRange = false;
	for(unsigned i = 0; i < Missile::allMissiles.size(); i++)
	{
		if(Missile::allMissiles[i]->getCurrentTarget() == this)
		{
			if (getPosition().getDistanceFromSQ(Missile::allMissiles[i]->getPosition()) < 250000)
			{
				missilesInRange = true;
				for (unsigned j = 0; j < pdTurrets.size(); ++j)
				{
					pdTurrets[j]->aim(Missile::allMissiles[i]->getPosition());
					pdTurrets[j]->fire();
					if (fighterDamageTime < timer->getTime())
					{
						//damage is temporary as shit!!
						Missile::allMissiles[i]->damage(2);
						fighterDamageTime = timer->getTime() + FIGHTERDAMAGETIMER;
					}
				}
			}			
		}
	}
	//aim point defense at fighters
	//this should be temporary until we come up with a faster solution1!!!
	//also, we really need to able to group fighters and missiles in the same array
	if(!missilesInRange)
	{
		for (unsigned i = 0; i < Fighter::allFighters.size(); ++i)
		{
			if (Fighter::allFighters[i]->getFaction() != faction &&
				(faction == FACTION_PIRATE || Fighter::allFighters[i]->getFaction() == FACTION_PIRATE))
			{
				if (getPosition().getDistanceFromSQ(Fighter::allFighters[i]->getPosition()) < 250000)
				{
					for (unsigned j = 0; j < pdTurrets.size(); ++j)
					{
						pdTurrets[j]->aim(Fighter::allFighters[i]->getPosition());
						pdTurrets[j]->fire();
						if (fighterDamageTime < timer->getTime())
						{
							//damage is temporary as shit!!
							Fighter::allFighters[i]->damage(2);
							fighterDamageTime = timer->getTime() + FIGHTERDAMAGETIMER;
						}
					}
				}
			}
		}
	}
}

//private function
//draw engine trails
void Ship::initEngineTrails()
{
	//create particle effecst and billboard effects
	for (int i = 0; i < ObjectManager::shipList[info.shipType]->getNumEngines(); ++i)
	{
		//get joint
		std::string jointName("exhaust");
		jointName += std::to_string(i+1);
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());

		//create particle system
		scene::IParticleSystemSceneNode *exhaust=scenemngr->addParticleSystemSceneNode(false,joint);
		scene::IParticleEmitter *em = exhaust->createBoxEmitter(core::aabbox3d<f32>(-15,-50,-15,15,50,15), core::vector3df(),200,500,
					video::SColor(0,255,255,255),       // darkest color
					video::SColor(0,255,255,255),       // brightest color
					300,500,0,                         // min and max age, angle
					core::dimension2df(5,5),  core::dimension2df(10,10));    
		exhaust->setEmitter(em);
		em->drop();
		exhaust->setMaterialTexture(0,vdriver->getTexture("res/textures/engine_trails.pcx"));
		exhaust->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		exhaust->setMaterialFlag(video::EMF_LIGHTING,false);
		engineParticles.push_back(exhaust);

		IBillboardSceneNode* corona = scenemngr->addBillboardSceneNode(joint,dimension2d<f32>(120,120),vector3df(0,0,10));
		corona->setMaterialTexture(0,vdriver->getTexture("res/textures/engine_corona.png"));
		corona->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		corona->setMaterialFlag(video::EMF_LIGHTING, false);
		coronaEffects.push_back(corona);

		//now add occlusion queries to corona effects
		vdriver->addOcclusionQuery(corona);
	}
}

//private function
//do all AI stuff here
void Ship::runAI()
{
	//make sure to comment this thoroughly!
	//and seperate into seperate functions if it becomes too big!!
	//TODO: REWRITE THIS STATE MACHINE
	//REIMPLEMENT ACCORDING TO PROPER STATE MACHINE GUIDELINES

	//updateStates();
	//std::cout << info.currentAIOrder << std::endl;
	switch (info.currentAIState)
	{
		//transitions go here
		//this is undergoing serious revision
		case AI_FLEEING:
		{
			if(!shipTarget)
			{
				info.currentAIState = AI_PATROLLING;
			}
			break;
		}
		case AI_ATTACKING:
		{
			if(!shipTarget)
			{
				//target probably destroyed so go back
				info.currentAIState = AI_PATROLLING;
			}
			if(info.hull < info.maxHull/2)
			{
				//fuck it run
				info.currentAIState = AI_FLEEING;
			}
			if(info.currentAIOrder != ORDER_NULL)
			{
				//do order
				info.currentAIState = AI_DOORDER;
			}
			break;
		}
		case AI_PATROLLING:
		{
			//search for targets and attack
			if(shipTarget && info.hull > info.maxHull/2 && 
				info.currentAIRole == SHIP_COMBAT || info.currentAIRole == SHIP_ESCORT)
			{
				info.currentAIState = AI_ATTACKING;
			}
			if(info.currentAIRole == SHIP_TRADER)
			{
				info.currentAIState = AI_TRADING;
			}
			if(shipFleet)
			{
				//check if we got an order
				if(info.currentAIOrder != ORDER_NULL && info.currentAIOrder != ORDER_ATTACKGENERAL)
				{
					//have something specific to do
					info.currentAIState = AI_DOORDER;
				}
				else
				{
					//no order so do whatever
					if(!shipTarget)
					{
						//make sure we don't follow ourselves
						if(shipFleet && this != shipFleet->getCommandingShip())
						{
							//rotate to the ship
							info.currentAIState = AI_FOLLOWING;
						}
					}
					else
					{
						info.currentAIState = AI_ATTACKING;
					}
				}
			}
			break;
		}
		case AI_TRADING:
		{
			if(info.currentAIRole != SHIP_TRADER)
			{
				info.currentAIState = AI_PATROLLING;
			}
			break;
		}
		case AI_FOLLOWING:
		{
			//follow the lead ship in the fleet
			//if we're following we have no order so just attack ships in range
			searchForTarget();
			if(shipTarget)
			{
				info.currentAIState = AI_ATTACKING;
			}
			break;
		}
		case AI_DOORDER:
		{
			if(info.currentAIOrder == ORDER_NULL)
			{
				//transition out
				info.currentAIState = AI_PATROLLING;
			}
			else
			{
				//if we have an order keep in the same state
				info.currentAIState = AI_DOORDER;
			}
			break;
		}
		default:
		{
			info.currentAIState = AI_PATROLLING;
			break;
		}
	}

	switch(info.currentAIState)
	{
		//actions go here
		case AI_FLEEING:
		{
			//do fleeing code here
			//fly away from painful things :(
			//recall fighters
			if (shipTarget)
			{
				//fly away from it and stop shooting
				vector3df targetVector = getPosition() - shipTarget->getPosition();
				targetVector = targetVector.getHorizontalAngle();

				setTargetRotation(targetVector);
			}
			//second objective is to find a friendly planet to warp to
			break;
		}
		case AI_ATTACKING:
		{
			//do attacking code here
			if (shipTarget)
			{
				runAttacking();
			}
			else
			{
				//if theres no target, change the state
				info.currentAIState = AI_PATROLLING;
			}
			break;
		}
		case AI_PATROLLING:
		{
			//crooze
			info.velocity = info.maxVelocity/2;
			//search for targets
			if (currentTime < timer->getTime())
			{
				searchForTarget();
				currentTime = timer->getTime() + AITIMER;
				if(shipTarget)
				{
					info.currentAIState = AI_ATTACKING;
				}
			}
			break;
		}
		case AI_TRADING:
		{
			//implement trading code here
			info.velocity = info.maxVelocity/2;
			//generally, traders should be neutral
			//generally
			//we find arbitrary space station for now and fly to it
			//shiptargets for traders are meant to be stations to fly to
			if(!shipTarget)
			{
				searchForFriendlyStation();
				//we should probably have a list of stations to travel to
				//make it fly to a random station
				//should generate it on the fly
			}
			else
			{
				//orient towards station
				vector3df targetVector = shipTarget->getPosition() - getPosition();
				targetVector = targetVector.getHorizontalAngle();

				setTargetRotation(targetVector);
				//why doesn't this proc?
				if(getPosition().getDistanceFrom(shipTarget->getPosition()) < 500)
				{
					//should probably switch space stations
					searchForFriendlyStation();
				}
			}
			break;
		}
		case AI_FOLLOWING:
		{
			//need to add a shitton of functionality for player control at this point
			vector3df targetVector = shipFleet->getCommandingShip()->getPosition() - getPosition();
			targetVector = targetVector.getHorizontalAngle();
		
			setTargetRotation(targetVector);

			//match ship speed
			f32 topShipVelocity = shipFleet->getCommandingShip()->getInfo().velocity;
			if(topShipVelocity < info.maxVelocity)
			{
				info.velocity = topShipVelocity;
			}
			else
			{
				info.velocity = info.maxVelocity;
			}
			break;
		}
		case AI_DOORDER:
		{
			//ai should so tuff here
			//call second statemachine
			doOrderSM();
			break;
		}
	}
}

void Ship::doOrderSM()
{
	//second statemachine
	//transitions
	//std::cout << info.currentAIOrder << std::endl;
	switch(info.currentAIOrder)
	{
		case ORDER_NULL:
		{
			//shouldnt be happening but ok
			info.currentAIState = AI_PATROLLING;
			break;
		}
		case ORDER_MOVETOLOCATION:
		{
			if(info.orderMove.getDistanceFromSQ(getPosition()) < 50000)
			{
				info.currentAIState = AI_PATROLLING;
				info.currentAIOrder = ORDER_NULL;
			}
			else
			{
				info.currentAIOrder = ORDER_MOVETOLOCATION;
			}
			break;
		}
		case ORDER_ATTACKGENERAL:
		{
			if(info.orderMove.getDistanceFromSQ(getPosition()) < 50000)
			{
				info.currentAIState = AI_PATROLLING;
				info.currentAIOrder = ORDER_NULL;
			}
			else
			{
				info.currentAIOrder = ORDER_ATTACKGENERAL;
			}
			break;
		}
		case ORDER_ATTACKTARGET:
		{
			if(!shipTarget)
			{
				info.currentAIOrder = ORDER_FOLLOW;				
			}
			else
			{
				info.currentAIOrder = ORDER_ATTACKTARGET;
			}
			break;
		}
		case ORDER_ATTACKANDMOVE:
		{
			break;
		}
		case ORDER_FOLLOW:
		{
			break;
		}
		case ORDER_FOLLOW_PASSIVE:
		{
			break;
		}
		default:
		{
			info.currentAIOrder = ORDER_FOLLOW;
			break;
		}
	}

	//actions
	switch(info.currentAIOrder)
	{
		case ORDER_NULL:
		{
			//shouldnt be happening but ok
			break;
		}		
		case ORDER_MOVETOLOCATION:
		{
			//do nothing but move to this location
			vector3df targetRotation;
			targetRotation = info.orderMove - getPosition();
			info.targetRotation = targetRotation.getHorizontalAngle(); 
			//info.targetRotation.X -= 360;
			//std::cerr << info.targetRotation.X << " " << getRotation().X << std::endl;
			info.velocity = info.maxVelocity;
			break;
		}
		case ORDER_ATTACKGENERAL:
		{
			//same thing as attack code
			//
			if(shipTarget)
			{
				//attack ship target
				runAttacking();
			}
			else
			{
				//else just move to point
				info.velocity = info.maxVelocity;
				vector3df targetRotation;
				targetRotation = info.orderMove - getPosition();
				info.targetRotation = targetRotation.getHorizontalAngle(); 
				searchForTarget();
			}

			break;
		}
		case ORDER_ATTACKTARGET:
		{
			if(shipTarget)
			{
				runAttacking();
			}
			break;
		}
		case ORDER_ATTACKANDMOVE:
		{
			vector3df targetRotation;
			targetRotation = info.orderMove - getPosition();
			info.targetRotation = targetRotation.getHorizontalAngle(); 
			//while attacking
			if(shipTarget)
			{
				if (getPosition().getDistanceFromSQ(shipTarget->getPosition()) > 20000000)
				{
					//break target
					shipTarget = 0;
				}
				//firing turrets ain't going to be that simple
				//ai has to handle the fact that it now has ENERGY
				//so we make it shoot in bursts
				if(info.energy > 0 && shouldFire)
					fireTurrets();
				else if(info.energy < info.maxEnergy)
				{
					shouldFire = false;
				}
				if(!shouldFire && info.energy > info.maxEnergy/2)
				{
					shouldFire = true;
				}
				setCorrectShieldAngle();
			}
			else
			{
				searchForTarget();
			}
			break;
		}
		case ORDER_FOLLOW:
		{
			if(!shipTarget)
			{
				searchForTarget();
				//need to add a shitton of functionality for player control at this point
				vector3df targetVector = shipFleet->getCommandingShip()->getPosition() - getPosition();
				targetVector = targetVector.getHorizontalAngle();

				setTargetRotation(targetVector);

				//match ship speed
				f32 topShipVelocity = shipFleet->getCommandingShip()->getInfo().velocity;
				if(topShipVelocity < info.maxVelocity)
				{
					info.velocity = topShipVelocity;
				}
				else
				{
					info.velocity = info.maxVelocity;
				}
			}
			else
			{
				runAttacking();
			}

			break;
		}
		case ORDER_FOLLOW_PASSIVE:
		{
			//need to add a shitton of functionality for player control at this point
			vector3df targetVector = shipFleet->getCommandingShip()->getPosition() - getPosition();
			targetVector = targetVector.getHorizontalAngle();

			setTargetRotation(targetVector);

			//match ship speed
			f32 topShipVelocity = shipFleet->getCommandingShip()->getInfo().velocity;
			if(topShipVelocity < info.maxVelocity)
			{
				info.velocity = topShipVelocity;
			}
			else
			{
				info.velocity = info.maxVelocity;
			}
			break;
		}
	}
}

//private function
//DEPRECATED
void Ship::updateStates()
{
	if (info.hull < info.maxHull/2)
	{
		//if hull is less than half, try to flee
		info.currentAIState = AI_FLEEING;
	}
	else if (shipFleet)
	{
		//if we're in a fleet
		//do stuff we're told to do
		//unless we're like the command ship
		//if we are then we resume whatever the fuck we were doing
		//find out if theres enemies nearby
		shipTarget = 0;
		searchForTarget();
		if(info.currentAIState != ORDER_NULL)
		{
			//have something specific to do
			info.currentAIState = AI_DOORDER;
		}
		else
		{
			if(!shipTarget)
				info.currentAIState = AI_FOLLOWING;
			else
				info.currentAIState = AI_ATTACKING;
		}
	}
	else if (shipTarget && info.currentAIState != AI_TRADING)
	{
		info.currentAIState = AI_ATTACKING;
	}
}

//private function
void Ship::runAttacking()
{
	//TODO: MAKE SURE SHIELD TURNS RIGHT
	if (getPosition().getDistanceFromSQ(shipTarget->getPosition()) > 20000000)
	{
		//break target
		shipTarget = 0;
	}
	else if (getPosition().getDistanceFromSQ(shipTarget->getPosition()) < 2250000)
	{
		//too close
		//turn away
		setTargetRotation(getTargetRotation() + vector3df(0, 90, 0));
		//make sure we keep our sides to the target ship at this range
		info.shieldDirection = SHIELD_STARBOARD;
	}
	else if (getPosition().getDistanceFromSQ(shipTarget->getPosition()) > 6250000)
	{
		//get closer
		//calculate vector to target
		vector3df targetVector = shipTarget->getPosition() - getPosition();
		targetVector = targetVector.getHorizontalAngle();
		if(targetVector.X > 70 || targetVector.X < -70)
			targetVector.X = 0;
		targetVector.Z = 0;
		setTargetRotation(targetVector);
		setCorrectShieldAngle(targetVector);
	}
	//do ship target AI;
	info.velocity = info.maxVelocity;
	launchFighters();
	//firing turrets ain't going to be that simple
	//ai has to handle the fact that it now has ENERGY
	//so we make it shoot in bursts
	if(info.energy > 0 && shouldFire)
		fireTurrets();
	else if(info.energy < info.maxEnergy)
	{
		shouldFire = false;
	}
	if(!shouldFire && info.energy > info.maxEnergy/2)
	{
		shouldFire = true;
	}
}

//private function
void Ship::searchForTarget()
{
	//search for targets
	for (unsigned i = 0; i < allShips.size(); i++)
	{
		//make sure we check factions first
		//because sqrts are expensive
		if ((allShips[i]->getInfo().currentFaction == FACTION_PIRATE && this->getInfo().currentFaction != FACTION_PIRATE) || 
			(allShips[i]->getInfo().currentFaction != FACTION_PIRATE && this->getInfo().currentFaction == FACTION_PIRATE))
		{
			//get ship
			if (allShips[i]->getPosition().getDistanceFrom(getPosition()) < 5000)
			{
				setTarget(allShips[i]);
				//info.currentAIState = AI_ATTACKING;
				return;
			}
		}
	}
}

//private function
void Ship::searchForFriendlyStation()
{
	//mostly use this for traders that keep going to different space stations
	//and completely destroy this system later
	//make more readable
	int i = rand() % SpaceStation::allStations.size();

	setTarget(SpaceStation::allStations[i]);
	
}

void Ship::setCorrectShieldAngle()
{
	//assume we have a shiptarget
	//grab the angle to the shiptarget
	vector3df targetRotation;
	targetRotation = shipTarget->getPosition() - getPosition();
	if(targetRotation.X > 315 && targetRotation.X < 45)
	{
		info.shieldDirection = SHIELD_FORE;
	}
	else if(targetRotation.X > 45 && targetRotation.X < 135)
	{
		info.shieldDirection = SHIELD_PORT;
	}
	else if(targetRotation.X > 135 && targetRotation.X < 225)
	{
		
	}
	else if(targetRotation.X > 225 && targetRotation.X < 315)
	{
		info.shieldDirection = SHIELD_STARBOARD;
	}
}

void Ship::setCorrectShieldAngle(const vector3df& targetRotation)
{
	if(targetRotation.X > 315 && targetRotation.X < 45)
	{
		info.shieldDirection = SHIELD_FORE;
	}
	else if(targetRotation.X > 45 && targetRotation.X < 135)
	{
		info.shieldDirection = SHIELD_PORT;
	}
	else if(targetRotation.X > 135 && targetRotation.X < 225)
	{
		//TODO: code to see how many arcs a shield gets
	}
	else if(targetRotation.X > 225 && targetRotation.X < 315)
	{
		info.shieldDirection = SHIELD_STARBOARD;
	}
}
