#include "stdafx.h"
#include "explosion.h"

const int EXPLOSIONLENGTH = 2000;

Explosion::Explosion(const vector3df& position) : Effect(EXPLOSIONLENGTH)
{
	
}

Explosion::~Explosion()
{
}

bool Explosion::run()
{
	return Effect::run();
}
