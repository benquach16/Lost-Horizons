#include "stdafx.h"
#include "muzzleflash.h"

#define MUZZLEFLASHLENGTH 100

Muzzleflash::Muzzleflash(IBoneSceneNode *parent, const vector3df &rotation) : Effect(MUZZLEFLASHLENGTH), parent(parent), particle(0)
{
	/*
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/misc/muzz.x"));
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	mesh->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	mesh->setRotation(rotation + vector3df(0,180,0));
	mesh->setScale(vector3df(0.5,0.5,0.5));
	mesh->setPosition(parent->getAbsolutePosition());*/
	particle = scenemngr->addParticleSystemSceneNode(false, parent);
	scene::IParticleEmitter *emitter = particle->createSphereEmitter(vector3df(0,0,0), 
		1.f, vector3df(0,0,0), 20, 200, video::SColor(255,0,0,0),video::SColor(255,255,255,255),500,1000,0,
		core::dimension2df(2,2),
		core::dimension2df(5,5));
	particle->setEmitter(emitter);
	particle->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/fire.png"));
	particle->setMaterialFlag(video::EMF_LIGHTING,false);
	particle->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	scene::IParticleAffector *af = particle->createAttractionAffector(vector3df(),-5.F);
	particle->addAffector(af);
	emitter->drop();
	af->drop();
}

Muzzleflash::~Muzzleflash()
{
	particle->remove();
}

bool Muzzleflash::run()
{
	return Effect::run();
}
