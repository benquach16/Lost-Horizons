#include "stdafx.h"
#include "visualsmanager.h"
#include "globals.h"

using namespace base;

#define NUMDUSTCLOUDS 20

VisualsManager::VisualsManager()
	: cam(scenemngr->getActiveCamera())
{
	for (unsigned i = 0; i < NUMDUSTCLOUDS; ++i)
	{
		scene::IBillboardSceneNode *s = scenemngr->addBillboardSceneNode(0,dimension2df(1000,1000),
			vector3df(cam->getPosition().X+rand()%2000-1000,cam->getPosition().Y+rand()%2000-1000,cam->getPosition().Z+rand()%2000-1000));
		s->setMaterialTexture(0,vdriver->getTexture("res/textures/dust.png"));
		s->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
		s->setMaterialFlag(video::EMF_LIGHTING,false);
		dust.push_back(s);
	}
}

VisualsManager::~VisualsManager()
{
	for (u32 i = 0; i < dust.size(); ++i)
		dust[i]->remove();
}

void VisualsManager::run()
{
	//make sure the distances are correct
	cam = scenemngr->getActiveCamera();
	for (unsigned i = 0; i < dust.size(); ++i)
	{
		if (dust[i]->getPosition().getDistanceFrom(cam->getPosition()) > 1000)
		{
			vector3df pos(cam->getPosition().X+rand()%2000-1000,cam->getPosition().Y+rand()%2000-1000,cam->getPosition().Z+rand()%2000-1000);
			dust[i]->setPosition(pos);
		}
	}
}
