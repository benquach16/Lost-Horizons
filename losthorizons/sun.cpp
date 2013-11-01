#include "stdafx.h"
#include "sun.h"
#include "globals.h"
#include <iostream>

using namespace base;

//default constructor
Sun::Sun()
	: Object(scenemngr->addSphereMesh("sun", 1000.f)), light(0), corona(0), corona2(0), lensFlare(0)
{
	//create the mesh and coronas
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	light = scenemngr->addLightSceneNode(mesh);
	light->setRadius(40000);

	corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(30000,30000), vector3df(0,0,0));
	corona->setMaterialTexture(0,  vdriver->getTexture("res/textures/particlewhite.bmp"));
	corona->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	corona2 = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(30000,30000), vector3df(0,0,0));
	corona2->setMaterialTexture(0, vdriver->getTexture("res/textures/engine_corona.png"));
	corona2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//add and occlussion query to this node!!
	vdriver->addOcclusionQuery(mesh, mesh->getMesh());
}

//parameterized juan
Sun::Sun(const vector3df &position, const vector3df &scale)
	: Object(scenemngr->addSphereMesh("sun", 1000.f), position, vector3df(0,0,0), scale), light(0), corona(0), lensFlare(new LensFlare(mesh))
{
	mesh->setMaterialFlag(video::EMF_LIGHTING, false);
	light = scenemngr->addLightSceneNode(mesh);
	light->setRadius(40000000);

	corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(30000,30000), position);
	corona->setMaterialTexture(0,  vdriver->getTexture("res/textures/particlewhite.bmp"));
	corona->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	corona2 = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(30000,30000), position);
	corona2->setMaterialTexture(0, vdriver->getTexture("res/textures/engine_corona.png"));
	corona2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);

	//add and occlussion query to this node!!
	//vdriver->addOcclusionQuery(mesh, mesh->getMesh());
}

Sun::~Sun()
{
	light->remove();
	corona->remove();
	corona2->remove();
}

bool Sun::run()
{
	//u32 occlusionResult = vdriver->getOcclusionQueryResult(mesh);
	//std::cout <<occlusionResult <<std::endl;
	//lensFlare->setStrength(occlusionResult/8000);
	return Object::run();
}
