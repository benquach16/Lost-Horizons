#include "stdafx.h"
#include "gamescene.h"
#include "globals.h"
#include "effect.h"
#include "player.h"
#include "sun.h"
#include "planet.h"
#include "spacestation.h"
#include "fighter.h"
#include "projectile.h"

using namespace base;

GameScene::GameScene(E_GAME_SCENE scene)
{
	switch (scene)
	{
	case SCENE_TAU_CETI:
		{
			skybox = scenemngr->addSkyBoxSceneNode(
				vdriver->getTexture("res/textures/skyboxes/1/space_top3.jpg"),
				vdriver->getTexture("res/textures/skyboxes/1/space_bottom4.jpg"),
				vdriver->getTexture("res/textures/skyboxes/1/space_left2.jpg"),
				vdriver->getTexture("res/textures/skyboxes/1/space_right1.jpg"),
				vdriver->getTexture("res/textures/skyboxes/1/space_front5.jpg"),
				vdriver->getTexture("res/textures/skyboxes/1/space_back6.jpg"));
			scenemngr->setAmbientLight(video::SColor(64,64,64,64));
			dynamicObjects.push(new Sun(vector3df(-20000,0,20000), vector3df(1.f,1.f,1.f)));

			dynamicObjects.push(new Planet(ObjectManager::E_PLANET_LIST::ARGREA, vector3df(12000,0,500)));
			dynamicObjects.push(new Planet(ObjectManager::E_PLANET_LIST::FARSTAR, vector3df(-40000,0,1000)));
			break;
		}
	default:
		{
			//SCENE_MAINMENU
			//create sun for menu background
			IBillboardSceneNode *corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(50000,50000), vector3df(-20000,500,70000));
			corona->setMaterialTexture(0, vdriver->getTexture("res/textures/particlewhite.bmp"));
			corona->setMaterialFlag(video::EMF_LIGHTING, false);
			corona->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			sceneObjects.push(corona);

			scene::IBillboardSceneNode *corona2 = scenemngr->addBillboardSceneNode(corona, dimension2d<f32>(130000,110000), vector3df(0,0,0));
			corona2->setMaterialTexture(0, vdriver->getTexture("res/textures/engine_corona.png"));
			corona2->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			sceneObjects.push(corona2);

			//setup menu background
			skybox = scenemngr->addSkyBoxSceneNode(
				vdriver->getTexture("res/textures/skyboxes/3/space_top3.jpg"),
				vdriver->getTexture("res/textures/skyboxes/3/space_bottom4.jpg"),
				vdriver->getTexture("res/textures/skyboxes/3/space_left2.jpg"),
				vdriver->getTexture("res/textures/skyboxes/3/space_right1.jpg"),
				vdriver->getTexture("res/textures/skyboxes/3/space_front5.jpg"),
				vdriver->getTexture("res/textures/skyboxes/3/space_back6.jpg"));
			scenemngr->setAmbientLight(video::SColor(64,64,64,64));	

			IParticleSystemSceneNode *nebula = scenemngr->addParticleSystemSceneNode(false);
			scene::IParticleSphereEmitter *em = nebula->createSphereEmitter(vector3df(-800,0,100), 10, vector3df(0.02f,0,0), 1, 1,
																			video::SColor(255,200,220,225), video::SColor(255,200,220,225), 15000, 25000, 0,
																			dimension2d<f32>(500,500), dimension2d<f32>(2000,2000));
			nebula->setEmitter(em);
			em->drop();
			nebula->setMaterialFlag(video::EMF_LIGHTING, false);
			nebula->setMaterialTexture(0, vdriver->getTexture("res/textures/fog.pcx"));
			nebula->setMaterialType(video::EMT_TRANSPARENT_ADD_COLOR);
			sceneObjects.push(nebula);

			scene::IParticleAffector *af = nebula->createFadeOutParticleAffector();
			nebula->addAffector(af);
			af->drop();
	
			IAnimatedMeshSceneNode *asteroids = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/planets/asteroid.x"));
			asteroids->setMaterialTexture(0, vdriver->getTexture("res/models/planets/roid.png"));
			asteroids->setPosition(vector3df(-20000,0,60000));
			asteroids->setScale(vector3df(8,8,8));
			sceneObjects.push(asteroids);
			break;
		}
	}
}

GameScene::~GameScene()
{
	skybox->remove();
	while (!sceneObjects.empty()) {
		sceneObjects.top()->remove();
		sceneObjects.pop();
	}
	while (!dynamicObjects.empty()) {
		delete dynamicObjects.top();
		dynamicObjects.pop();
	}
	for (u32 i = 0; i < Effect::allEffects.size(); ++i)
		delete Effect::allEffects[i];
	Effect::allEffects.clear();
	//delete all ships currently in the scene except for the player
	while (Ship::allShips.size() > 0)
		delete Ship::allShips.back();
	while (!SpaceStation::allStations.empty())
		delete SpaceStation::allStations.back();
	while (!Fighter::allFighters.empty())
		delete Fighter::allFighters.back();
	while (!Projectile::allProjectiles.empty())
		delete Projectile::allProjectiles.back();
}

void GameScene::run()
{
	//run all of the objects
	unsigned i = 0;
	std::vector<int> deletedObjects(Object::allObjects.size());
	//unsigned objSize = Object::allObjects.size();
	while (i < Object::allObjects.size())
	{
	   
		if (Object::allObjects[i]->run())
			i++;
		else
		{
			//TODO :: DO NOT DO CLEANUP IMMEDIATELY!!!!!!
			//need to make sure that all objects know that ths object is deleted first
			//make sure we iterate over our list at least once before we can delete
			//delete Object::allObjects[i];
			if(Object::allObjects[i]->getIterations() > 3)
			{
				delete Object::allObjects[i];
				//i++;
			}
			else
			{
				Object::allObjects[i]->incrementIterations();
				i++;
			}
		}
	}
	//run effects
	i = 0;
	//objSize = Effect::allEffects.size();
	while (i < Effect::allEffects.size()) {
		if (Effect::allEffects[i]->run())
			i++;
		else {
			delete Effect::allEffects[i];
			Effect::allEffects[i] = Effect::allEffects.back();
			Effect::allEffects.pop_back();
		}
	}

	
	
}
