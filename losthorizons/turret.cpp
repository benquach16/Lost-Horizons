#include "stdafx.h"
#include "turret.h"
#include "globals.h"
#include "ship.h"
#include <iostream>

using namespace base;

//BEGIN TURRETSLOT
TurretSlot::TurretSlot(const turretInformation &properties, IBoneSceneNode *joint, const E_TURRET_CLASS turretClass, Ship* parent) : 
	joint(joint), childTurret(0), properties(properties), rotationOffset(properties.rotation), parent(parent)
{
	//we have not one but two scene nodes beecause joints fuck things up
	offset = scenemngr->addEmptySceneNode(joint);
	aimPoint = scenemngr->addEmptySceneNode();
	offset->setRotation(rotationOffset);
}

void TurretSlot::assignTurret(const ObjectManager::E_ITEM_LIST turretType)
{
	//ensure that its a turret or else we will crash
	if (ObjectManager::itemList[turretType]->getItemType() == ITEM_TURRET) 
	{
		//make sure that the childturret pointer is clear
		removeTurret();
		childTurret = new Turret(turretType, offset, this);
	}
}

bool TurretSlot::getCanFire()
{
	return canFire;
}

bool TurretSlot::fire()
{
	if (childTurret && canFire) 
	{
		//flip the y axis because it is fucked
		vector3df realAim = currentAim;
		realAim.Y += 180;
		childTurret->fire(realAim);
		return true;
	}
	else
		return false;
}

void TurretSlot::removeTurret()
{
	if (childTurret)
		delete childTurret;
	childTurret = 0;
}

void TurretSlot::drawArc()
{
	//we're going to do some fun math here
}

void TurretSlot::aim(const core::vector3df &point)
{
	aimPoint->setPosition(joint->getAbsolutePosition());
	if (childTurret) 
	{
		//do some math to find the angle to face this point
		
		const float x = offset->getAbsolutePosition().X - point.X;
		const float y = point.Y - offset->getAbsolutePosition().Y;
		const float z = offset->getAbsolutePosition().Z - point.Z;
		float angleY = std::atan2(x,z)*(180.f/PI);

		float t  = sqrt(x*x+z*z);
		float angleX = std::atan2(t,y)*(180.f/PI);
		
		angleX -= 90;

		currentAim = vector3df(angleX, angleY,0);
		const int difference = (360 - properties.arc)/2;
		//THIS IS THE CAUSE OF ALL OUR PROBLEMS
		//THIS IS WHY WE CANT HAVE NICE THINGS
		//THIS FUCKING LINE
		//we have serious issues with negatives for some reason
		//probably some issues with angles so we're going to fix it
		/*
		vector3df positionDifference;
		positionDifference.Y = point.Y - parent->getPosition().Y;
		positionDifference.X = parent->getPosition().X - point.X;
		positionDifference.Z = parent->getPosition().Z - point.Z;*/
		vector3df diff = currentAim;// = positionDifference.getHorizontalAngle();

		
		//std::cout << diff.Y << std::endl;

		//normalize angles
		float tmp = parent->getRotation().Y - rotationOffset.Y;
  
		
		float left = (diff.Y + difference);

		float right = (diff.Y - difference);

		if ( left < tmp || right > tmp) 
		{
			//inside the arc horizontally
			//pass rotation to the turret so we dont do math again unnecessarily
			//draw so player knows which turrets can shoot
			//angleY -= parent->getRotation().Y;
			//angleY += 180 - offset->getRotation().Y;
			//std::cout << tmp << " left : " << left << " right : " << right << std::endl;
			diff.Y += -parent->getRotation().Y + offset->getRotation().Y;
			childTurret->aim(diff);
			canFire = true;

		} 
		else 
		{
			//just reset the aim and not shoot
			//good shit
			resetAim();
		}
	} 
	else 
	{
		//no turret so 
		canFire = false;
	}
}

void TurretSlot::resetAim()
{
	if (childTurret) {
		childTurret->aim(vector3df(0,180,0));
		canFire = false;
	}
}

TurretSlot::~TurretSlot()
{
	//make sure we clear up memory
	removeTurret();
}

Ship* TurretSlot::getParent() const
{
	return parent;
}

const vector3df& TurretSlot::getCurrentAim() const
{
	return currentAim;
}

const vector3df& TurretSlot::getPosition() const
{
	return aimPoint->getPosition();
}

const ObjectManager::E_ITEM_LIST TurretSlot::getTurretType() const
{
	if (childTurret) {
		return childTurret->getTurretType();
	} else {
		return ObjectManager::ITEM_COUNT;
	}
}

//END TURRETSLOT


//BEGIN TURRET
Turret::Turret() : turretType(ObjectManager::E_ITEM_LIST::ANTIMATTERI)
{
	//default constructor
}

Turret::Turret(const ObjectManager::E_ITEM_LIST turretType, ISceneNode *parent, TurretSlot *parentSlot) : 
	Object(((TurretProperties*)ObjectManager::itemList[turretType])->getFilename(), vector3df(0,0,0), vector3df(0,0,0),
	((TurretProperties*)ObjectManager::itemList[turretType])->getScale()),
	turretType(turretType), shootJoint(0), parentSlot(parentSlot), shootTimer(0)
{
	shootJoint = mesh->getJointNode("shoot");
	mesh->setParent(parent);
	setNormalMap(vdriver->getTexture(((TurretProperties*)ObjectManager::itemList[turretType])->getNormalMap()));
}

Turret::~Turret()
{
}

bool Turret::run()
{
	return Object::run();
}

void Turret::aim(const core::vector3df &rotation)
{
	core::vector3df temp(getRotation());
	if (temp.Y < rotation.Y) {
		temp.Y += ((TurretProperties*)ObjectManager::itemList[turretType])->getMaxTurn()*frameDeltaTime;
	} else if (temp.Y > rotation.Y) {
		temp.Y -= ((TurretProperties*)ObjectManager::itemList[turretType])->getMaxTurn()*frameDeltaTime;
	}
	temp.Y = rotation.Y;//turret rotation is still messed up
	setRotation(temp);
}

void Turret::fire(const vector3df &rotation)
{
	//stopgap fix so we can have dynamically firing weapons
	//since volley fire looks pretty unrealistic
	//probably should modify this later
	if(shootTimer < timer->getTime())
	{
		//for now, projectile gets an ID. change to ship pointer later
		Projectile *p = new Projectile(parentSlot->getParent()->getID(),*((TurretProperties*)ObjectManager::itemList[turretType]), shootJoint->getAbsolutePosition(), rotation);
		Muzzleflash *m = new Muzzleflash(shootJoint, getRotation());
		sound->play3D(((TurretProperties*)ObjectManager::itemList[turretType])->getSoundFilename(), getPosition());
		parentSlot->getParent()->modifyEnergy(-((TurretProperties*)ObjectManager::itemList[turretType])->getEnergyUse());
		int i = ((TurretProperties*)ObjectManager::itemList[turretType])->getReloadSpeed();
		shootTimer = timer->getTime() + i + rand()%i-(i/2);
	}
}

const Ship* Turret::getParent() const
{
	return parentSlot->getParent();
}
