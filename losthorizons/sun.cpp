#include "stdafx.h"
#include "sun.h"

//default constructor
Sun::Sun() : Object(scenemngr->addSphereMesh("sun", 1000.f))
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	light = scenemngr->addLightSceneNode(mesh);
	light->setRadius(10000);
}

//parameterized juan
Sun::Sun(const vector3df &position, const vector3df &scale) : 
	Object(scenemngr->addSphereMesh("sun", 1000.f), position, vector3df(0,0,0), scale)
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	light = scenemngr->addLightSceneNode(mesh);
	light->setRadius(30000);
}

Sun::~Sun()
{
	light->remove();
}
