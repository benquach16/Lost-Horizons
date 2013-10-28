#ifndef _VISUALSMANAGER_H_
#define _VISUALSMANAGER_H_

#include "stdafx.h"

using namespace irr;

//the visuals manager has a very simple job - to make the game look cool
//it simply controls the dust and nebula fog in space

#define NUMDUSTCLOUDS 20

class VisualsManager
{
public:
	VisualsManager();
	~VisualsManager();
	void run();

private:
	scene::ICameraSceneNode *cam;
	scene::IBillboardSceneNode* dust[NUMDUSTCLOUDS];
};

#endif
