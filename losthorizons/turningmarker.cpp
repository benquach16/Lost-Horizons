#include "stdafx.h"
#include "turningmarker.h"
#include "globals.h"

using namespace base;

TurningMarker::TurningMarker()
	: XYcircle(scenemngr->addCubeSceneNode(10.f, 0, -1, core::vector3df(), core::vector3df(), core::vector3df(30,0,30))),
	  YZcircle(scenemngr->addCubeSceneNode(10.f, 0, -1, core::vector3df(), core::vector3df(), core::vector3df(0,30,30))),
	  arrow(scenemngr->addCubeSceneNode(10.f, 0, -1, core::vector3df(), core::vector3df(), core::vector3df(30,0,30)))
{
	XYcircle->setMaterialTexture(0, vdriver->getTexture("res/textures/circle.png"));
	XYcircle->setMaterialFlag(video::EMF_LIGHTING,false);
	XYcircle->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	XYcircle->setMaterialFlag(video::EMF_ZBUFFER,true);

	YZcircle->setMaterialTexture(0, vdriver->getTexture("res/textures/circle.png"));
	YZcircle->setMaterialFlag(video::EMF_LIGHTING,false);
	YZcircle->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	YZcircle->setMaterialFlag(video::EMF_ZBUFFER,true);

	arrow->setMaterialTexture(0,vdriver->getTexture("res/textures/arrow.png"));
	arrow->setMaterialFlag(video::EMF_LIGHTING, false);
	arrow->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);

	setVisible(false);
}

TurningMarker::~TurningMarker()
{
	XYcircle->remove();
	YZcircle->remove();
	arrow->remove();
}

void TurningMarker::run(const core::vector3df &pos, const core::vector3df &rot, const core::vector3df &targetRot)
{
	//make sure to orient everything correctly
	XYcircle->setPosition(pos);
	YZcircle->setPosition(pos);
	arrow->setPosition(pos);
	YZcircle->setRotation(targetRot);
	matrix4 mat = arrow->getAbsoluteTransformation();
	//mat.setRotationCenter(player->getPosition(), vector3df(0,0,50));
	//mat.setRotationDegrees(player->getRotation());
	//scenemngr->getMeshManipulator()->transform(arrow->getMesh(), mat);
	arrow->setRotation(targetRot);
	
	//make sure to hide this when the palyer is close enough to target rotation
	//so we have less clutter
	setVisible(rot.Y - 3 > targetRot.Y || rot.Y + 3 < targetRot.Y ||
			   rot.X - 3 > targetRot.X || rot.X + 3 < targetRot.X);
}

//protected function
void TurningMarker::setVisible(bool visible)
{
	XYcircle->setVisible(visible);
	YZcircle->setVisible(visible);
	arrow->setVisible(visible);
}
