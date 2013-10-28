#include "stdafx.h"
#include "projectile.h"
#include "globals.h"
#include <iostream>

using namespace base;

std::vector<Projectile*> Projectile::allProjectiles;

Projectile::Projectile(u16 ID, const TurretProperties &turretProps, const vector3df &position, const vector3df &rotation)
	: Object(L"res/models/projectile.X", turretProps.getProjectileTex().c_str(), position, rotation, turretProps.getProjectileScale()),
	  originalPosition(position), ID(ID), damage(turretProps.getDamage()), range(turretProps.getRange()),
	  velocity(turretProps.getProjectileSpeed()), index(allProjectiles.size())
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	allProjectiles.push_back(this);
}

Projectile::~Projectile()
{
	//swap with back and pop
	allProjectiles[index] = allProjectiles.back();
	allProjectiles[index]->index = index;
	allProjectiles.pop_back();
}

void Projectile::run(f32 frameDeltaTime)
{
	Object::run(frameDeltaTime);
	if (!checkIfOutOfRange()) {
		movement(frameDeltaTime);
		//check if collides with a ship
		for (unsigned i = 0; i < Ship::allShips.size(); i++) {
			if (ID != Ship::allShips[i]->getID() && Ship::allShips[i]->getBoundingBox().isPointInside(getPosition())) {
				//hit a target
				//std::cout << "HIT TARGET" << std::endl;
				Impact *impact = new Impact(getPosition());
				Ship::allShips[i]->damage(damage);
				delete this;
				return;
			}
		}
	} else {
		delete this;
	}
}

//protected function
void Projectile::movement(f32 frameDeltaTime)
{
	//similar movement code as ships
	vector3df sPos = getPosition();
	f32 i = getRotation().Y;
	f32 z = -(getRotation().X);	//if i dont do this the ship doesnt rotate right


	sPos.Y = (f32)(frameDeltaTime*velocity*(sin(z*3.14/180)));
	sPos.Y += getPosition().Y;

	sPos.X = (f32)(frameDeltaTime*velocity*(sin(i*3.14/180)));
	sPos.X += getPosition().X;

	sPos.Z = (f32)(frameDeltaTime*velocity*(cos(i*3.14/180)));
	sPos.Z += getPosition().Z;

	setPosition(sPos);
}

//protected function
bool Projectile::checkIfOutOfRange()
{
	//basic math to check distances
	//dont do sqrt for speed
	const float x = originalPosition.X - getPosition().X;
	const float y = originalPosition.Y - getPosition().Y;
	const float z = originalPosition.Z - getPosition().Z;

	if ((x*x + y*y + z*z) > (range*range)) {
		//out of range
		return true;
	}
	return false;
}
