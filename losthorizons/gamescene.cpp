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
	if(scene == E_MAINMENU_SCENE)
	{
		//create sun for menu background
		IBillboardSceneNode *corona = scenemngr->addBillboardSceneNode(0, dimension2d<f32>(50000,50000), vector3df(-20000,500,70000));
		corona->setMaterialTexture(0, vdriver->getTexture("res/particlewhite.bmp"));
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
		asteroids->setMaterialTexture(0, vdriver->getTexture("res/roid.jpg"));
		asteroids->setPosition(vector3df(-20000,0,60000));
		asteroids->setScale(vector3df(8,8,8));
		sceneObjects.push(asteroids);

	}
	else if(scene == E_TAU_CETI_SCENE)
	{
		skybox = scenemngr->addSkyBoxSceneNode(
			vdriver->getTexture("res/textures/skyboxes/1/space_top3.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_bottom4.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_left2.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_right1.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_front5.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_back6.jpg"));
		scenemngr->setAmbientLight(SColor(64,64,64,64));


	}
}

GameScene::~GameScene()
{
	skybox->remove();
	while(!sceneObjects.empty())
	{
		sceneObjects.top()->remove();
		sceneObjects.pop();
	}
}

void GameScene::run(float frameDeltaTime)
{
	//run through all the objects in the scene
	for(std::list<Ship*>::iterator i = Ship::allShips.begin(); i!= Ship::allShips.end(); i++)
	{
		(*i)->run(frameDeltaTime);
	}
}

PlayerCamera *GameScene::createPlayerCam(const vector3df &position)
{
	PlayerCamera *ret = new PlayerCamera(graphics, position);
	return ret;
}

Player *GameScene::createPlayer(const ShipProperties &shipProps, const vector3df &position, const vector3df &rotation)
{
	Player *ret = new Player(graphics, shipProps, position, rotation);
	return ret;
}

PlayerCamera *GameScene::getCurrentSceneCamera()
{
	return playerCam;
}
