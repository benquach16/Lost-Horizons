#ifndef _VISUALSMANAGER_H_
#define _VISUALSMANAGER_H_

#include "stdafx.h"

//the visuals manager has a very simple job - to make the game look cool
//it simply controls the dust and nebula fog in space

#define NUMDUSTCLOUDS 20

class VisualsManager
{
public:
	VisualsManager();
	~VisualsManager();
	void run();

protected:
	irr::scene::ICameraSceneNode *cam;
	irr::scene::IBillboardSceneNode* dust[NUMDUSTCLOUDS];
};

#endif
