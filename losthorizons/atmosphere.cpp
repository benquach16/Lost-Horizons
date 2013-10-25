#include "stdafx.h"
#include "atmosphere.h"
#include "globals.h"

using namespace base;

Atmosphere::Atmosphere(const core::vector3df& position) : atmosphereSceneNode(scenemngr->addCubeSceneNode(1))
{
	atmosphereSceneNode->setScale(core::vector3df(0,13500,13500));
	atmosphereSceneNode->setPosition(position);
	atmosphereSceneNode->setMaterialTexture(0,vdriver->getTexture("res/textures/atmos.png"));
	atmosphereSceneNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	atmosphereSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
}

Atmosphere::~Atmosphere()
{
	atmosphereSceneNode->remove();
}

void Atmosphere::run()
{
	//rotate to face the camera
	//not quite a billboard which is why we need a seperate class
	core::vector3df difference = scenemngr->getActiveCamera()->getAbsolutePosition() - atmosphereSceneNode->getAbsolutePosition();
	difference = difference.getHorizontalAngle();
	atmosphereSceneNode->setRotation(difference);
}
