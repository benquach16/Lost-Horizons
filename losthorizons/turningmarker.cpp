#include "turningmarker.h"
#include "globals.h"

using namespace base;

TurningMarker::TurningMarker(Player *player) : player(player), XYcircle(0), YZcircle(0), arrow(0)
{
	XYcircle = scenemngr->addCubeSceneNode();
	XYcircle->setScale(core::vector3df(30,0,30));
	XYcircle->setMaterialTexture(0, vdriver->getTexture("res/textures/circle.png"));
	XYcircle->setMaterialFlag(video::EMF_LIGHTING,false);
	XYcircle->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	XYcircle->setMaterialFlag(video::EMF_ZBUFFER,true);

	YZcircle = scenemngr->addCubeSceneNode();
	YZcircle->setScale(core::vector3df(0,30,30));
	YZcircle->setMaterialTexture(0, vdriver->getTexture("res/textures/circle.png"));
	YZcircle->setMaterialFlag(video::EMF_LIGHTING,false);
	YZcircle->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	YZcircle->setMaterialFlag(video::EMF_ZBUFFER,true);

	arrow = scenemngr->addCubeSceneNode();
	arrow->setScale(core::vector3df(30,0,30));
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

void TurningMarker::run()
{
	//make sure to orient everything correctly
	XYcircle->setPosition(player->getPosition());
	YZcircle->setPosition(player->getPosition());
	arrow->setPosition(player->getPosition());
	YZcircle->setRotation(player->getTargetRotation());
	matrix4 mat = arrow->getAbsoluteTransformation();
	//mat.setRotationCenter(player->getPosition(), vector3df(0,0,50));
	//mat.setRotationDegrees(player->getRotation());
	//scenemngr->getMeshManipulator()->transform(arrow->getMesh(), mat);
	arrow->setRotation(player->getTargetRotation());
	
	//make sure to hide this when the palyer is close enough to target rotation
	//so we have less clutter
	setVisible(player->getRotation().Y - 3 > player->getTargetRotation().Y || player->getRotation().Y + 3 < player->getTargetRotation().Y ||
			   player->getRotation().X - 3 > player->getTargetRotation().X || player->getRotation().X + 3 < player->getTargetRotation().X);
}

//protected function
void TurningMarker::setVisible(bool visible)
{
	XYcircle->setVisible(visible);
	YZcircle->setVisible(visible);
	arrow->setVisible(visible);
}
