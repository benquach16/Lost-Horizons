#include "stdafx.h"
#include "ship.h"
#include "globals.h"
#include <iostream>

using namespace base;

//set up static elements
std::vector<Ship*> Ship::allShips;
wchar_t *Ship::subsystemNames[] = { L"Bridge", L"Deck 1", L"Deck 2", L"Elevator",
	L"Engine", L"Warp Drive", L"Shield Generator", L"Power Plant",
	L"Heavy Weapons", L"Medium Weapons", L"Light Weapons", L"Point Defense"};

//time between ai updates to save cpu speed
#define AITIMER 100

Ship::Ship(const E_GAME_FACTION &faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, *ObjectManager::shipList[shipType], position, rotation, faction), info(shipType, faction),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), energyTimer(0),
	  fighterDamageTime(0), fighterUpdateTime(0), index(allShips.size())
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
	setMediumTurret(ObjectManager::E_ITEM_LIST::RAILGUNI,3);
	setMediumTurret(ObjectManager::E_ITEM_LIST::RAILGUNI,2);
	setMediumTurret(ObjectManager::E_ITEM_LIST::RAILGUNI,1);
	setMediumTurret(ObjectManager::E_ITEM_LIST::RAILGUNI,0);
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
	if(faction == FACTION_NEUTRAL)
		info.currentAIState = AI_TRADING;
}

Ship::Ship(const u16 ID, const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation)
	: TargetableObject(ID, *ObjectManager::shipList[info.shipType], position, rotation, info.currentFaction), info(info),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), fighterDamageTime(0), energyTimer(0),
	  fighterUpdateTime(0), index(allShips.size())
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
}

//copy constructor
Ship::Ship(const Ship *s, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, *ObjectManager::shipList[s->info.shipType], position, rotation, s->faction), info(s->info),
	  shipTarget(0), shieldTimer(0), currentTime(0), fighterLaunchTime(0), fighterDamageTime(0), energyTimer(0),
	  fighterUpdateTime(0), index(allShips.size())
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Ship object created" << std::endl;

	//add it to the ships list
	allShips.push_back(this);

	for (unsigned i = 0; i < SUBSYSTEM_COUNT; ++i) {
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
	allShips[index] = allShips.back();
	allShips[index]->index = index;
	allShips.pop_back();
}

bool Ship::run()
{
	if (info.hull > 0)
	{
		if (info.docked)
		{
			//if the ship is docked it most certaintly cannot move
		}
		else
		{
			//make sure its alive to do anything
			//if the crew is 0 the ship is effectively dead
			//make it rotate to its targetted rotation first
			//and movement
			rotate();
			aimTurrets();
			
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
			if(info.energy < info.maxEnergy && energyTimer < timer->getTime())
			{
				//piggyback off the shield recharge timer
				info.energy++;
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
		info.velocity += (5+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::decreaseVelocity()
{
	if (info.velocity > -info.maxVelocity)
		info.velocity -= (1+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::fireTurrets()
{
	//lets do this in a way that doesn't involve middlemen
	if(info.energy > 5)
	{
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
	if (info.shield > 0)
	{
		info.shield -= damage;
	}
	else if (info.armor > 0)
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
		subsystems[rand()%SUBSYSTEM_COUNT] -= rand()%100;
	}
}

void Ship::damage(int damage, const vector3df& projectilePosition)
{
	//bigger damage function to take into account shield rotation
	//calculate the angle so we can see if it hit the shield or not
	//we only do x and z because y is only a formality in this game
	float x = projectilePosition.X - getPosition().X;
	float z = projectilePosition.Z - getPosition().Z;
	
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



//all private functions go under here
//private function
//rotates ship to point
void Ship::rotate()
{
	vector3df currentRot = getRotation();
	if (currentRot != info.targetRotation) {
		if (currentRot.Y != info.targetRotation.Y) {
			f32 slowY = currentRot.Z = 0.5f*abs(currentRot.Y - info.targetRotation.Y);
			if (slowY > info.maxTurn)
				slowY = info.maxTurn;
			if (currentRot.Z > 4)
				currentRot.Z = 4.f;
			if (currentRot.Y < info.targetRotation.Y) {
				//rotate right
				currentRot.Y += slowY*frameDeltaTime;
				currentRot.Z = -currentRot.Z;
			} else {
				//rotate left
				currentRot.Y -= slowY*frameDeltaTime;
			}
		}
		if (currentRot.X != info.targetRotation.X) {
			f32 slowX = 0.5f*abs(currentRot.X - info.targetRotation.X);
			if (slowX > info.maxTurn)
				slowX = info.maxTurn;
			if (currentRot.X > info.targetRotation.X) {
				//rotate up
				//make sure we cant rotate past 70 up and down
				if(currentRot.X > -70)
					currentRot.X -= slowX*frameDeltaTime;
			} else {
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
			mediumTurrets[i]->aim(shipTarget->getPosition());
		}
		for (unsigned i = 0; i < lightTurrets.size(); i++)
		{
			lightTurrets[i]->aim(shipTarget->getPosition());
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

	//aim point defense at fighters
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
						Fighter::allFighters[i]->damage(2);
						fighterDamageTime = timer->getTime() + 2520;
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
	updateStates();
	if (info.currentAIState == AI_FLEEING)
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

	}
	else if (info.currentAIState == AI_ATTACKING)
	{
		//do attacking code here
		if (shipTarget)
		{
			if (getPosition().getDistanceFrom(shipTarget->getPosition()) > 20000)
			{
				//break target
				shipTarget = 0;
			}
			else if (getPosition().getDistanceFrom(shipTarget->getPosition()) < 1000)
			{
				//too close
				//turn away
				setTargetRotation(getTargetRotation() + vector3df(0, (f32)(rand() % 180), 0));
			}
			else if (getPosition().getDistanceFrom(shipTarget->getPosition()) > 2000)
			{
				//get closer
				//calculate vector to target
				vector3df targetVector = shipTarget->getPosition() - getPosition();
				targetVector = targetVector.getHorizontalAngle();
				if(targetVector.X > 70 || targetVector.X < -70)
						targetVector.X = 0;
				targetVector.Z = 0;
				setTargetRotation(targetVector);
			}
			//do ship target AI;
			info.velocity = info.maxVelocity;
			launchFighters();
			fireTurrets();
		}
		else
		{
			//if theres no target, change the state
			info.currentAIState = AI_PATROLLING;
		}
	}
	else if (info.currentAIState == AI_PATROLLING)
	{
		//crooze
		info.velocity = info.maxVelocity/2;
		//search for targets
		if (currentTime < timer->getTime())
		{
			searchForTarget();
			currentTime = timer->getTime() + AITIMER;
		}
	}
	else if (info.currentAIState == AI_TRADING)
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
	}
	else if(info.currentAIState == AI_FOLLOWING)
	{
		//need to add a shitton of functionality for player control at this point
	}
}

//private function
void Ship::updateStates()
{
	if (info.hull < info.maxHull/2)
	{
		//if hull is less than half, try to flee
		info.currentAIState = AI_FLEEING;
	}
	else if (shipTarget && info.currentAIState != AI_TRADING)
	{
		info.currentAIState = AI_ATTACKING;
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
			if (allShips[i]->getPosition().getDistanceFrom(getPosition()) < 5000)
			{
				setTarget(allShips[i]);
				info.currentAIState = AI_ATTACKING;
			}
		}
	}
}

//private function
void Ship::searchForFriendlyStation()
{
	//mostly use this for traders that keep going to different space stations
	//make more readable
	int i = rand() % SpaceStation::allStations.size();

	setTarget(SpaceStation::allStations[i]);
	
}
