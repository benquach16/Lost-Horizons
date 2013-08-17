#include "stdafx.h"
#include "impact.h"

const int IMPACTLENGTH = 200;

Impact::Impact(const vector3df &position) : Effect(IMPACTLENGTH), fireParticles(0)
{
	fireParticles = scenemngr->addParticleSystemSceneNode(false, 0, -1, position);

	scene::IParticleEmitter *emitter = fireParticles->createSphereEmitter(vector3df(0,0,0), 
		1.f, vector3df(0,0,0), 3, 5, video::SColor(255,0,0,0),video::SColor(255,255,255,255),500,1000,0,
		core::dimension2df(1,1),
		core::dimension2df(3,3));

	fireParticles->setEmitter(emitter);
	fireParticles->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/fire.png"));
	fireParticles->setMaterialFlag(video::EMF_LIGHTING,false);
	fireParticles->setMaterialType(video::EMT_TRANSPARENT_VERTEX_ALPHA);
	scene::IParticleAffector *af = fireParticles->createAttractionAffector(position,-50.F);
	fireParticles->addAffector(af);
	emitter->drop();
	af->drop();
}

Impact::~Impact()
{
	fireParticles->remove();
}


void Impact::run()
{
	Effect::run();
}

