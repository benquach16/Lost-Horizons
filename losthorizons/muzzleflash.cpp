#include "stdafx.h"
#include "muzzleflash.h"
#include "globals.h"

using namespace base;

#define MUZZLEFLASHLENGTH 200

Muzzleflash::Muzzleflash(scene::IBoneSceneNode *parent, const core::vector3df &rotation)
	: Effect(MUZZLEFLASHLENGTH), parent(parent), particle(0)
{
	/*
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/muzz.x"));
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	mesh->setRotation(rotation + vector3df(0,180,0));
	mesh->setScale(vector3df(0.5,0.5,0.5));
	mesh->setPosition(parent->getAbsolutePosition());*/
	particle = scenemngr->addParticleSystemSceneNode(false, parent);
	scene::IParticleEmitter *emitter = particle->createSphereEmitter(core::vector3df(0,0,0), 
		1.f, core::vector3df(0,0,0), 20, 20, video::SColor(255,0,0,0),video::SColor(255,255,255,255),500,1000,0,
		core::dimension2df(2,2),
		core::dimension2df(5,5));
	particle->setEmitter(emitter);
	particle->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/fire.png"));
	particle->setMaterialFlag(video::EMF_LIGHTING,false);
	particle->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	scene::IParticleAffector *af = particle->createFadeOutParticleAffector(video::SColor(0,0,0,0), 100);
	particle->addAffector(af);
	emitter->drop();
	af->drop();

	smoke = scenemngr->addParticleSystemSceneNode(false, parent);
	scene::IParticleEmitter *emitter2 = smoke->createSphereEmitter(core::vector3df(0,0,0), 
		3.f, core::vector3df(0,0,0), 20, 20, video::SColor(128,0,0,0),video::SColor(128,128,128,128),500,1000,0,
		core::dimension2df(2,2),
		core::dimension2df(5,5));
	smoke->setEmitter(emitter2);
	smoke->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/smoke.png"));
	smoke->setMaterialFlag(video::EMF_LIGHTING,false);
	smoke->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	emitter2->drop();
}

Muzzleflash::~Muzzleflash()
{
	particle->remove();
	smoke->remove();
}

bool Muzzleflash::run()
{
	return Effect::run();
}
