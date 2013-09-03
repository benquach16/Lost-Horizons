#include "stdafx.h"
#include "muzzleflash.h"

const int MUZZLEFLASHLENGTH = 100;

Muzzleflash::Muzzleflash(IBoneSceneNode *parent) : Effect(MUZZLEFLASHLENGTH), parent(parent), mesh(0)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/muzz.x"), parent);
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
}

Muzzleflash::~Muzzleflash()
{
	mesh->remove();
}

bool Muzzleflash::run()
{
	return Effect::run();
}
