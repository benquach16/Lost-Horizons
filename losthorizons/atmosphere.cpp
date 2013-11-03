#include "stdafx.h"
#include "atmosphere.h"
#include "globals.h"

using namespace base;

Atmosphere::Atmosphere(const core::vector3df& position)
	: atmosphereSceneNode(scenemngr->addCubeSceneNode(1, 0, -1, position, core::vector3df(), core::vector3df(0,13500,13500)))
{
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
	atmosphereSceneNode->setRotation((scenemngr->getActiveCamera()->getAbsolutePosition() - atmosphereSceneNode->getAbsolutePosition()).getHorizontalAngle());
}
