#include "stdafx.h"
#include "muzzleflash.h"

const int MUZZLEFLASHLENGTH = 100;

Muzzleflash::Muzzleflash(IBoneSceneNode *parent, const vector3df &rotation) : Effect(MUZZLEFLASHLENGTH), parent(parent), mesh(0)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/muzz.x"));
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	mesh->setRotation(rotation + vector3df(0,180,0));
	mesh->setScale(vector3df(0.5,0.5,0.5));
	mesh->setPosition(parent->getAbsolutePosition());
}

Muzzleflash::~Muzzleflash()
{
	mesh->remove();
}

bool Muzzleflash::run()
{
	return Effect::run();
}
