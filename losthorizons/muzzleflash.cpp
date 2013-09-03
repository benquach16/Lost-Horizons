#include "stdafx.h"
#include "muzzleflash.h"

const int MUZZLEFLASHLENGTH = 500;

Muzzleflash::Muzzleflash(const IBoneSceneNode *parent) : Effect(MUZZLEFLASHLENGTH), parent(parent)
{
}

Muzzleflash::~Muzzleflash()
{
}

bool Muzzleflash::run()
{
	return Effect::run();
}
