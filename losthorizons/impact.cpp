#include "stdafx.h"
#include "impact.h"
#include "globals.h"

using namespace base;

#define IMPACTLENGTH 1000

Impact::Impact(const core::vector3df &position) : Effect(IMPACTLENGTH), fireParticles(0), debrisParticles(0)
{
	//play a single sound only once
	sound->play3D("res/sounds/hit.wav", position);

	//create particle effects
	fireParticles = scenemngr->addParticleSystemSceneNode(false, 0, -1, position);

	scene::IParticleEmitter *emitter = fireParticles->createSphereEmitter(vector3df(0,0,0), 
		1.f, vector3df(0,0,0), 20, 200, video::SColor(255,0,0,0),video::SColor(255,255,255,255),500,1000,0,
		core::dimension2df(2,2),
		core::dimension2df(10,10));

	fireParticles->setEmitter(emitter);
	fireParticles->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/fire.png"));
	fireParticles->setMaterialFlag(video::EMF_LIGHTING,false);
	fireParticles->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
	scene::IParticleAffector *af = fireParticles->createAttractionAffector(position,-5.F);
	fireParticles->addAffector(af);
	emitter->drop();
	af->drop();
}

Impact::~Impact()
{
	fireParticles->remove();
	//debrisParticles->remove();
}


bool Impact::run()
{
	return Effect::run();
}

