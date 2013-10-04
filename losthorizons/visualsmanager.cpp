#include "stdafx.h"
#include "visualsmanager.h"

const unsigned NUMDUSTCLOUDS = 20;

VisualsManager::VisualsManager()
{
	scene::ICameraSceneNode *cam = scenemngr->getActiveCamera();
	for (unsigned i = 0; i < NUMDUSTCLOUDS; ++i)
	{
		scene::IBillboardSceneNode *s = scenemngr->addBillboardSceneNode(0,dimension2df(1000,1000),
			vector3df(cam->getPosition().X+rand()%2000-1000,cam->getPosition().Y+rand()%2000-1000,cam->getPosition().Z+rand()%2000-1000));
		s->setMaterialTexture(0,vdriver->getTexture("res/textures/dust.png"));
		s->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		s->setMaterialFlag(video::EMF_LIGHTING,false);
		dustManager.push_back(s);
	}
}

VisualsManager::~VisualsManager()
{
	for (u32 i = 0; i < dustManager.size(); ++i)
		dustManager[i]->remove();
}

void VisualsManager::run()
{
	//make sure the distances are correct
	scene::ICameraSceneNode *cam = scenemngr->getActiveCamera();
	for (unsigned i = 0; i < dustManager.size(); ++i)
	{
		if (dustManager[i]->getPosition().getDistanceFrom(cam->getPosition()) > 1000)
		{
			vector3df pos(cam->getPosition().X+rand()%2000-1000,cam->getPosition().Y+rand()%2000-1000,cam->getPosition().Z+rand()%2000-1000);
			dustManager[i]->setPosition(pos);
		}
	}
}
