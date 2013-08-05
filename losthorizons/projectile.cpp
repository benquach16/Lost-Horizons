#include "stdafx.h"
#include "projectile.h"

std::list<Projectile*> Projectile::allProjectiles;

Projectile::Projectile(const vector3df &position, const vector3df &rotation, const TurretProperties &turretProps) : 
	Object(L"res/models/projectile.X", turretProps.getProjectileTex().c_str(), position, rotation, turretProps.getProjectileScale()),
	originalPosition(position), velocity(turretProps.getProjectileSpeed()), range(turretProps.getRange())
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	allProjectiles.push_front(this);
	it = allProjectiles.begin();
}

Projectile::~Projectile()
{
	allProjectiles.erase(it);
}

void Projectile::run(f32 frameDeltaTime)
{
	Object::run(frameDeltaTime);
	if(!checkIfOutOfRange())
	{
		movement(frameDeltaTime);
	}
	else
	{
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

	if((x*x + y*y + z*z) > (range*range))
	{
		//out of range
		return true;
	}
	return false;
}
