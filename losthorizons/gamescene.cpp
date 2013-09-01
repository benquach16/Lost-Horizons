#include "stdafx.h"
#include "gamescene.h"
#include <iostream>

GameScene::GameScene()
{
}

GameScene::GameScene(IrrlichtDevice *graphics, E_GAMESCENES scene) : graphics(graphics), scene(scene)
{
	//setup camera for menu scene
	playerCam = createPlayerCam();
	if (scene == E_MAINMENU_SCENE)
	{
		//create sun for menu background
		IBillboardSceneNode *corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(50000,50000), vector3df(-20000,500,70000));
		corona->setMaterialTexture(0, vdriver->getTexture("res/textures/particlewhite.bmp"));
		corona->setMaterialFlag(EMF_LIGHTING, false);
		corona->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
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
		scenemngr->setAmbientLight(SColor(64,64,64,64));	

		IParticleSystemSceneNode *nebula = scenemngr->addParticleSystemSceneNode(false);
		scene::IParticleSphereEmitter *em = nebula->createSphereEmitter(vector3df(-800,0,100), 10, vector3df(0.02f,0,0), 1, 1,
																		SColor(255,200,220,225), SColor(255,200,220,225), 15000, 25000, 0,
																		dimension2d<f32>(500,500), dimension2d<f32>(2000,2000));
		nebula->setEmitter(em);
		em->drop();
		nebula->setMaterialFlag(EMF_LIGHTING, false);
		nebula->setMaterialTexture(0, vdriver->getTexture("res/textures/fog.pcx"));
		nebula->setMaterialType(EMT_TRANSPARENT_ADD_COLOR);
		sceneObjects.push(nebula);

		scene::IParticleAffector *af = nebula->createFadeOutParticleAffector();
		nebula->addAffector(af);
		af->drop();
	
		IAnimatedMeshSceneNode *asteroids = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh("res/models/planets/asteroid.x"));
		asteroids->setMaterialTexture(0, vdriver->getTexture("res/models/planets/roid.png"));
		asteroids->setPosition(vector3df(-20000,0,60000));
		asteroids->setScale(vector3df(8,8,8));
		sceneObjects.push(asteroids);

	}
	else if (scene == E_TAU_CETI_SCENE)
	{
		skybox = scenemngr->addSkyBoxSceneNode(
			vdriver->getTexture("res/textures/skyboxes/1/space_top3.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_bottom4.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_left2.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_right1.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_front5.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_back6.jpg"));
		scenemngr->setAmbientLight(SColor(64,64,64,64));
		dynamicObjects.push(createSun(vector3df(-20000,0,20000)));

		Planet *argrea = new Planet(ObjectManager::E_PLANET_LIST::ARGREA, vector3df(12000,0,500));
		dynamicObjects.push(argrea);
		Planet *farstar = new Planet(ObjectManager::E_PLANET_LIST::FARSTAR, vector3df(-40000,0,1000));
		dynamicObjects.push(farstar);


	}
}

GameScene::~GameScene()
{
	skybox->remove();
	while (!sceneObjects.empty())
	{
		sceneObjects.top()->remove();
		sceneObjects.pop();
	}
	while (!dynamicObjects.empty())
	{
		delete dynamicObjects.top();
		dynamicObjects.pop();
	}
	//delete all ships currently in the scene except for the player
	while (Ship::allShips.size() > 1)
		delete Ship::allShips.front();
	while (SpaceStation::allStations.size() > 1)
		delete SpaceStation::allStations.front();

	while(!Effect::allEffects.empty())
	{
		Effect::allEffects.erase(Effect::allEffects.begin());
	}
}

void GameScene::run(f32 frameDeltaTime)
{
	/*
	//run through all the objects in the scene
	for (std::list<Ship*>::iterator i = Ship::allShips.begin(), next; i != Ship::allShips.end(); i = next)
	{
		next = i;
		next++;
		(*i)->run(frameDeltaTime);
	}
	//initialize 2 iterators because we want to delete the object whenever we have to
	//so we dont lose the iterator!!!!!!!
	for (std::list<Projectile*>::iterator i = Projectile::allProjectiles.begin(), next; i != Projectile::allProjectiles.end(); i = next)
	{
		next = i;
		next++;
		(*i)->run(frameDeltaTime);
	}*/
	for (std::list<Object*>::iterator i = Object::allObjects.begin(), next; i != Object::allObjects.end(); i = next)
	{
		next = i;
		next++;
		(*i)->run(frameDeltaTime);
	}
	//run effects
	for(unsigned i = 0; i < Effect::allEffects.size(); i++)
	{
		if(!Effect::allEffects[i]->run())
		{
			
			Effect::allEffects.erase(Effect::allEffects.begin()+i);
		}
	}
}
 
//functions for creating scene objects
PlayerCamera *GameScene::createPlayerCam(const vector3df &position)
{
	return new PlayerCamera(graphics, position);
}

Ship *GameScene::createShip(const E_GAME_FACTIONS &faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
{
	if (Ship::allShips.empty())
		return new Player(faction, shipType, position, rotation);
	else
		return new Ship(faction, shipType, position, rotation);
}

Ship *GameScene::createShip(u32 ID, const ShipInformation &info, const vector3df &position, const vector3df &rotation)
{
	if (Ship::allShips.empty())
		return new Player(info, position, rotation);
	else
		return new Ship(ID, info, position, rotation);
}

Sun *GameScene::createSun(const vector3df &position, const vector3df &scale)
{
	return new Sun(position, scale);
}

SpaceStation *GameScene::createStation(const E_GAME_FACTIONS faction, ObjectManager::E_STATION_LIST stationType, const vector3df &position,
									   const vector3df& rotation)
{
	return new SpaceStation(faction, stationType, position, rotation);
}

PlayerCamera *GameScene::getCurrentSceneCamera()
{
	return playerCam;
}

E_GAMESCENES GameScene::getScene()
{
	return scene;
}
