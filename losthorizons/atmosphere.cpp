#include "stdafx.h"
#include "atmosphere.h"

Atmosphere::Atmosphere(const vector3df& position) : atmosphereSceneNode(0)
{
	atmosphereSceneNode = scenemngr->addCubeSceneNode(1);
	atmosphereSceneNode->setScale(vector3df(0,13500,13500));
	atmosphereSceneNode->setPosition(position);
	atmosphereSceneNode->setMaterialTexture(0,vdriver->getTexture("res/textures/atmos.png"));
	atmosphereSceneNode->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	atmosphereSceneNode->setMaterialFlag(video::EMF_LIGHTING, false);
}

Atmosphere::~Atmosphere()
{

}

void Atmosphere::run()
{
	//rotate to face the camera
	//not quite a billboard which is why we need a seperate class
	ICameraSceneNode *cam = scenemngr->getActiveCamera();
	vector3df difference = cam->getAbsolutePosition() - atmosphereSceneNode->getAbsolutePosition();
	difference = difference.getHorizontalAngle();
	atmosphereSceneNode->setRotation(difference);
}
