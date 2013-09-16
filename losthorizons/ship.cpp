#include "stdafx.h"
#include "ship.h"
#include <iostream>

std::list<Ship*> Ship::allShips;

//time between ai updates to save cpu speed
const unsigned AITIMER = 100;

Ship::Ship(const E_GAME_FACTIONS &faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, ObjectManager::shipList[shipType], position, rotation, faction), info(shipType, faction), shipTarget(0), shieldTimer(0),
	currentTime(0), fighterLaunchTime(0), fighterDamageTime(0)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	std::cout << '[' << ID << "]Ship object created" << std::endl;

	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();
	
	//set up the ship turrets
	initTurrets();
	initEngineTrails();
	initSubsystems();

	setNormalMap(vdriver->getTexture(ObjectManager::shipList[shipType].getNormalMap().c_str()));
	setMediumTurret(ObjectManager::turretList[0],3);
	setMediumTurret(ObjectManager::turretList[0],2);
	setMediumTurret(ObjectManager::turretList[0],1);
	setMediumTurret(ObjectManager::turretList[0],0);
	setLightTurret(ObjectManager::turretList[1],0);
	setLightTurret(ObjectManager::turretList[1],1);
	setLightTurret(ObjectManager::turretList[1],2);
	setLightTurret(ObjectManager::turretList[1],3);
	setPDTurret(ObjectManager::turretList[2], 0);
	setPDTurret(ObjectManager::turretList[2], 1);
	setPDTurret(ObjectManager::turretList[2], 2);
	setPDTurret(ObjectManager::turretList[2], 3);
	info.inventory.addItem(ObjectManager::E_ITEM_LIST::WATER, 100);
}

Ship::Ship(u32 ID, const ShipInformation &info, const vector3df &position, const vector3df &rotation)
	: TargetableObject(ID, ObjectManager::shipList[info.shipType], position, rotation, info.currentFaction), info(info), shipTarget(0), shieldTimer(0)
{
	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();

	//set up the ship turrets
	initTurrets();
	initEngineTrails();
	initSubsystems();
}

//copy constructor
Ship::Ship(const Ship *s, const vector3df &position, const vector3df &rotation)
	: TargetableObject(nextID++, ObjectManager::shipList[s->info.shipType], position, rotation, s->faction), info(s->info), shipTarget(0), shieldTimer(0)
{
	//ID 0 is reserved for the player, and the player is created first and only once
	if (nextID == 0)
		nextID++;

	//add it to the ships list
	allShips.push_front(this);
	it = allShips.begin();
	initTurrets();
	initEngineTrails();
	initSubsystems();
}

//assignmennt operator
Ship& Ship::operator=(const Ship *s)
{
	if (s && this != s)
	{
		//TODO: ASSISNGMENT OPERATOR!!!
		mesh->remove();
		mesh = s->mesh;
		info = s->info;

	}
	return *this;
}

Ship::~Ship()
{
	allShips.erase(it);
	//clear memory we allocated
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
	removeThisFromTargets();
}

void Ship::run(f32 frameDeltaTime)
{
	TargetableObject::run(frameDeltaTime);
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
			rotate(frameDeltaTime);
			aimTurrets(frameDeltaTime);
			
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

			movement(frameDeltaTime);

			//recharge shields
			if (info.subsystems[E_SUBSYSTEM_SHIELD].health > 0)
			{
				if(info.shield < info.maxShield)
				{
					if(shieldTimer < timer->getTime())
					{
						info.shield++;
						shieldTimer  = timer->getTime() + 100;
					}
				}
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
		delete this;
	}
}

//increases velocity based on how fast the ship is going
void Ship::increaseVelocity(f32 frameDeltaTime)
{
	if (info.velocity < info.maxVelocity)
		info.velocity += (5+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::decreaseVelocity(f32 frameDeltaTime)
{
	if (info.velocity > -info.maxVelocity)
		info.velocity -= (1+abs(info.velocity)/2)*frameDeltaTime;
}

void Ship::fireTurrets()
{
	//lets do this in a way that doesn't involve middlemen
	for (unsigned i = 0; i < mediumTurrets.size(); ++i) {
		mediumTurrets[i]->fire();
	}
	for (unsigned i = 0; i < lightTurrets.size(); i++)
	{
		lightTurrets[i]->fire();
	}
}

void Ship::damage(int val)
{
	//do damage stuff here
	//check shields, then armor then hull
	if(info.shield > 0)
	{
		info.shield -= val;
	}
	else if(info.armor > 0)
	{
		info.armor -= val;
	}
	else
	{
		//damage hull
		info.hull -= val;
		//since armor and hull are damaged, kill off some of the crew
		info.crew -= (rand()%info.crew)/4;
		//and damage a subsystem
		info.subsystems[rand()%info.subsystems.size()].health -= rand()%100;
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

void Ship::removeTarget()
{
	shipTarget = 0;
}

//turret setter functions
void Ship::setMediumTurret(const TurretProperties &props, unsigned slot)
{
	if (slot < mediumTurrets.size())
		mediumTurrets[slot]->assignTurret(props);
}

void Ship::setLightTurret(const TurretProperties &props, unsigned slot)
{
	if (slot < lightTurrets.size())
		lightTurrets[slot]->assignTurret(props);
}

void Ship::setPDTurret(const TurretProperties &props, unsigned slot)
{
	if (slot < pdTurrets.size())
		pdTurrets[slot]->assignTurret(props);
}

void Ship::setFaction(E_GAME_FACTIONS newFaction)
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
	return E_OBJECT_SHIP;
}

Inventory& Ship::getInventory()
{
	return info.inventory;
}

bool Ship::isPlayer() const
{
	return ID == 0;
}

void Ship::removeThisFromTargets()
{
	//loop thru ship list and remove this ship if it is a target
	for (std::list<Ship*>::iterator i = allShips.begin(); i != allShips.end(); ++i)
	{
		if ((*i)->getShipTarget() == this)
			(*i)->setTarget(0);
	}
}

void Ship::dockWithTarget()
{
	//check if target is a spaec station

	if (getShipTarget() && getShipTarget()->getTargetableObjectType() == E_OBJECT_SPACESTATION)
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
			Fighter *f = new Fighter(ObjectManager::E_FIGHTER_LIST::DRAGONFLY, 
				getPosition(), getRotation(), info.currentFaction, this);
			fighterLaunchTime = timer->getTime() + 500;
			info.fighters--;
		}
	
	}

}

void Ship::warpToTarget()
{

	if (shipTarget && info.subsystems[E_SUBSYSTEM_WARPDRIVE].health > 0)
	{
		//make sure we have a target
		//save to variable first to avoid multiple sqrt operations
		f32 dist = getPosition().getDistanceFrom(shipTarget->getPosition());

		if (dist > 10000)
		{
			//make sure we can't 'point jump' ship targets
			vector3df diff = shipTarget->getPosition() - getPosition();
			diff = diff.getHorizontalAngle();
			setTargetRotation(diff);
			info.velocity = 0;
			info.warping = true;
		}
	}
	
}

//all private functions go under here
//private function
//rotates ship to point
void Ship::rotate(f32 frameDeltaTime)
{
	vector3df sRot = getRotation();
	vector3df rotSlow = getRotation();
	if (getRotation().Y < info.targetRotation.Y)	//ship wants to rotate right
	{
		rotSlow.Y = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));	//simulate inertia
		rotSlow.Z = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));
		if (rotSlow.Z > 4)
			rotSlow.Z = 4.f;
		if (rotSlow.X > 4)
			rotSlow.X = 4.f;
		if (rotSlow.Y > info.maxTurn)
			rotSlow.Y = info.maxTurn;
		sRot.Y += rotSlow.Y*frameDeltaTime;
		sRot.Z = -rotSlow.Z;
		setRotation(sRot);
	}
	if (getRotation().Y > info.targetRotation.Y)	//ship wants to rotate left
	{
		rotSlow.Y = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));	//simulate inertia
		rotSlow.Z = 0.5f*(abs(getRotation().Y-info.targetRotation.Y));
		if (rotSlow.Z > 4)
			rotSlow.Z = 4;
		if (rotSlow.Y > info.maxTurn)
			rotSlow.Y = info.maxTurn;
		sRot.Y -= rotSlow.Y*frameDeltaTime;
		sRot.Z = rotSlow.Z;
		setRotation(sRot);
	}
	if (getRotation().X > info.targetRotation.X)	//turn up
	{
		sRot = getRotation();
		rotSlow.X = 0.5f*(abs(getRotation().X-info.targetRotation.X));
		if (rotSlow.X > info.maxTurn)
			rotSlow.X = info.maxTurn;
		sRot.X -= rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
	if (getRotation().X < info.targetRotation.X)	//turn down
	{
		sRot = getRotation();
		rotSlow.X = 0.5f*(abs(getRotation().X-info.targetRotation.X));
		if (rotSlow.X > info.maxTurn)
			rotSlow.X = info.maxTurn;
		sRot.X += rotSlow.X*frameDeltaTime;
		setRotation(sRot);
	}
}

//private function
void Ship::movement(f32 frameDeltaTime)
{
	vector3df sPos = getPosition();
	f32 i = getRotation().Y;
	f32 z = -(getRotation().X);	//if i dont do this the ship doesnt rotate right

	sPos.Y = (f32)(frameDeltaTime*info.velocity*(sin(z*3.14/180)));
	sPos.Y += getPosition().Y;

	sPos.X = (f32)(frameDeltaTime*info.velocity*(sin(i*3.14/180)));
	sPos.X += getPosition().X;

	sPos.Z = (f32)(frameDeltaTime*info.velocity*(cos(i*3.14/180)));
	sPos.Z += getPosition().Z;

	//smooth out ship movement
	vector3df finalPos = sPos*0.8f+getPosition()*0.2f;
	setPosition(finalPos);
}
//private function
//initialises the turret slot classes for each ship
void Ship::initTurrets()
{
	//we create new turret slots and assign them to the ship
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxHTurrets(); ++i)
	{
		//get the bone name and set it to the string
		std::string jointName("heavy_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType].mediumTurrets[i], joint, E_CLASS_HEAVY, this);
		mediumTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxMTurrets(); ++i)
	{
		//get the bone name and set it to the string
		std::string jointName("turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType].mediumTurrets[i], joint, E_CLASS_MEDIUM, this);
		mediumTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxLTurrets(); ++i)
	{
		std::string jointName("secondary_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(ObjectManager::shipList[info.shipType].lightTurrets[i], joint, E_CLASS_LIGHT, this);
		lightTurrets.push_back(t);
	}
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getMaxPTurrets(); ++i)
	{
		std::string jointName("light_turret_0");
		std::string tmp = std::to_string(i+1);
		jointName += tmp;
		scene::IBoneSceneNode *joint = mesh->getJointNode(jointName.c_str());
		TurretSlot *t = new TurretSlot(turretInformation(), joint, E_CLASS_PD, this);
		pdTurrets.push_back(t);
	}
}

//private function
//aims turrets at current target
void Ship::aimTurrets(float frameDeltaTime)
{
	if (shipTarget)
	{
		//if has target
		for (unsigned i = 0; i < heavyTurrets.size(); i++)
		{
			heavyTurrets[i]->aim(shipTarget->getPosition(), frameDeltaTime);
		}
		for (unsigned i = 0; i < mediumTurrets.size(); ++i)
		{
			mediumTurrets[i]->aim(shipTarget->getPosition(), frameDeltaTime);
		}
		for (unsigned i = 0; i < lightTurrets.size(); i++)
		{
			lightTurrets[i]->aim(shipTarget->getPosition(), frameDeltaTime);
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
	for (std::list<Fighter*>::iterator i = Fighter::allFighters.begin(), next; i != Fighter::allFighters.end(); i = next)
	{
		next = i;
		++next;
		if (((*i)->getFaction() == E_FACTION_PIRATE && faction != E_FACTION_PIRATE) || 
			((*i)->getFaction() != E_FACTION_PIRATE && faction == E_FACTION_PIRATE))
		{
			if (getPosition().getDistanceFromSQ((*i)->getPosition()) < 250000)
			{
				for (unsigned n = 0; n < pdTurrets.size(); ++n)
				{
					pdTurrets[n]->aim((*i)->getPosition(), frameDeltaTime);
					pdTurrets[n]->fire();
					if (fighterDamageTime < timer->getTime())
					{
						(*i)->damage(2);
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
	for (int i = 0; i < ObjectManager::shipList[info.shipType].getNumEngines(); ++i)
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
//add subsystems
void Ship::initSubsystems()
{
	info.subsystems.push_back(Subsystem(L"Bridge"));
	info.subsystems.push_back(Subsystem(L"Deck 1"));
	info.subsystems.push_back(Subsystem(L"Deck 2"));
	info.subsystems.push_back(Subsystem(L"Elevator"));
	info.subsystems.push_back(Subsystem(L"Engine"));
	info.subsystems.push_back(Subsystem(L"Warp Drive"));
	info.subsystems.push_back(Subsystem(L"Shield Generator"));
	info.subsystems.push_back(Subsystem(L"Power Plant"));
	info.subsystems.push_back(Subsystem(L"Heavy Weapons"));
	info.subsystems.push_back(Subsystem(L"Medium Weapons"));
	info.subsystems.push_back(Subsystem(L"Light Weapons"));
	info.subsystems.push_back(Subsystem(L"Point Defense"));
}

//private function
//do all AI stuff here
void Ship::runAI()
{
	//make sure to comment this thoroughly!
	//and seperate into seperate functions if it becomes too big!!
	updateStates();
	if (info.currentAIState == STATE_FLEEING)
	{
		//do fleeing code here
		//fly away from painful things :(
	}
	else if (info.currentAIState == STATE_ATTACKING)
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
			info.currentAIState = STATE_PATROLLING;
		}
	}
	else if (info.currentAIState == STATE_PATROLLING)
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
}

//private function
void Ship::updateStates()
{
	if (info.hull < info.maxHull/2)
	{
		//if hull is less than half, try to flee
		info.currentAIState = STATE_FLEEING;
	}
	else if (shipTarget)
	{
		info.currentAIState = STATE_ATTACKING;
	}
}

//private function
void Ship::searchForTarget()
{
	//search for targets
	for (std::list<Ship*>::iterator i = allShips.begin(); i != allShips.end(); ++i)
	{
		//make sure we check factions first
		//because sqrts are expensive
		if (((*i)->getInfo().currentFaction == E_FACTION_PIRATE && this->getInfo().currentFaction != E_FACTION_PIRATE) || 
			((*i)->getInfo().currentFaction != E_FACTION_PIRATE && this->getInfo().currentFaction == E_FACTION_PIRATE))
		{
			if ((*i)->getPosition().getDistanceFrom(getPosition()) < 5000)
			{
				setTarget(*i);
				info.currentAIState = STATE_ATTACKING;
			}
		}
	}
}
