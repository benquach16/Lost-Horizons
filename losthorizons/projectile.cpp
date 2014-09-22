#include "stdafx.h"
#include "projectile.h"
#include "globals.h"
#include <iostream>

using namespace base;
using namespace irr;
using namespace core;
using namespace video;

std::vector<Projectile*> Projectile::allProjectiles;

Projectile::Projectile(const u16 ID, const TurretProperties &turretProps, const vector3df &position, const vector3df &rotation)
	: Object(L"res/models/projectile.X", turretProps.getProjectileTex(), position, rotation, turretProps.getProjectileScale()),
	  originalPosition(position), ID(ID), damage(turretProps.getDamage()), range(turretProps.getRange()),
	  velocity(turretProps.getProjectileSpeed()), index(allProjectiles.size())
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	allProjectiles.push_back(this);
	rangeSqrt = range * range;
	/*
	system=scenemngr->addParticleSystemSceneNode(false);
	aabbox3df box = mesh->getTransformedBoundingBox();
	box.MaxEdge -= getPosition();
	box.MinEdge -= getPosition();
	scene::IParticleEmitter *em = system->createBoxEmitter(
		box,
		vector3df(0,0,0),
		400,400,
		SColor(255,255,255,255),
		SColor(255,255,255,255),
		1000,
		1000,
		0,
		dimension2df(2,2),
		dimension2df(2,2));
	system->setEmitter(em);
	em->drop();
	system->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/smoke2.png"));
	system->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	system->setMaterialFlag(video::EMF_LIGHTING,false);*/
}

Projectile::~Projectile()
{
	//swap with back and pop
	//system->remove();
	allProjectiles[index] = allProjectiles.back();
	allProjectiles[index]->index = index;
	allProjectiles.pop_back();
}

bool Projectile::run()
{
	if (inRange()) {
		movement();
		//check if collides with a ship
		unsigned i = 0;
		while (Object::run() && i < Ship::allShips.size()) {
			if (ID != Ship::allShips[i]->getID() && Ship::allShips[i]->getBoundingBox().isPointInside(getPosition())) {
				//hit a target
				//std::cout << "HIT TARGET" << std::endl;
				Impact *impact = new Impact(getPosition());
				Ship::allShips[i]->damage(damage, getPosition());
				remove();
			} else {
				i++;
			}
		}
	} else {
		remove();
	}
	return Object::run();
}

//protected function
void Projectile::movement()
{
	//similar movement code as ships
	


	const f32 temp = frameDeltaTime*velocity;
	const f32 X = sin(getRotation().Y*PI/180)*temp + getPosition().X;
	const f32 Y = sin(-getRotation().X*PI/180)*temp + getPosition().Y;
	const f32 Z = cos(getRotation().Y*PI/180)*temp + getPosition().Z;
	//system->setPosition(getPosition());
	setPosition(core::vector3df(X,Y,Z));
}

//protected function
bool Projectile::inRange()
{
	//basic math to check distances
	//dont do sqrt for speed
	const float x = originalPosition.X - getPosition().X;
	const float y = originalPosition.Y - getPosition().Y;
	const float z = originalPosition.Z - getPosition().Z;
	return x*x + y*y + z*z < rangeSqrt;
}
