#include "stdafx.h"
#include "explosion.h"
#include "globals.h"

using namespace base;

#define EXPLOSIONLENGTH 3000

Explosion::Explosion(const core::vector3df& position) : Effect(EXPLOSIONLENGTH), fireParticles(0), shockwave(0)
{
	//intialize particle system
	sound->play3D("res/sounds/reactor_explo.wav", position);
	fireParticles = scenemngr->addParticleSystemSceneNode(false, 0, -1, position);
	IParticleEmitter *emitter = fireParticles->createSphereEmitter(vector3df(0,0,0), 20,
		vector3df(0,0,0), 100, 200, video::SColor(0,255,255,255), video::SColor(0,255,255,255),
		2000, 4000, 0, dimension2df(75,75), dimension2df(150,150));
	fireParticles->setEmitter(emitter);

	fireParticles->setMaterialTexture(0, vdriver->getTexture("res/textures/engine_trails.pcx"));
	fireParticles->setMaterialFlag(video::EMF_LIGHTING, false);
	fireParticles->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	IParticleAffector *af = fireParticles->createAttractionAffector(position, -100.f);
	fireParticles->addAffector(af);
	emitter->drop();
	af->drop();

	shockwave = scenemngr->addCubeSceneNode(5);
	shockwave->setScale(core::vector3df(5,0,5));
	shockwave->setMaterialTexture(0,vdriver->getTexture("res/textures/fx/shockwave.png"));
	shockwave->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	shockwave->setPosition(position);
	shockwave->setMaterialFlag(video::EMF_LIGHTING, false);

}

Explosion::~Explosion()
{
	fireParticles->remove();
	shockwave->remove();
}

bool Explosion::run()
{
	core::vector3df tmp = shockwave->getScale();
	tmp.X+=3;
	tmp.Z+=3;
	shockwave->setScale(tmp);
	return Effect::run();

}
