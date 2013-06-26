#include "stdafx.h"
#include "gamescene.h"

GameScene::GameScene()
{
}

GameScene::GameScene(IrrlichtDevice *graphics) : graphics(graphics)
{
	//create scene
	scene::ISceneNode *skybox = graphics->getSceneManager()->addSkyBoxSceneNode(
			vdriver->getTexture("res/textures/skyboxes/1/space_top3.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_bottom4.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_left2.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_right1.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_front5.jpg"),
			vdriver->getTexture("res/textures/skyboxes/1/space_back6.jpg"));
}

GameScene::GameScene(IrrlichtDevice *graphics, E_GAMESCENES scene) : graphics(graphics)
{
	if(scene == E_MAINMENU_SCENE)
	{

	}
}

GameScene::~GameScene()
{
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
