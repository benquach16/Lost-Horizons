//#include "stdafx.h"
#include "gamescene.h"

GameScene::GameScene()
{
}

GameScene::GameScene(IrrlichtDevice *graphics) : graphics(graphics)
{

}

GameScene::~GameScene()
{
}

void GameScene::run()
{
	//run through all the objects in the scene
	for(std::list<Ship*>::iterator i = Ship::allShips.begin(); i!= Ship::allShips.end(); i++)
	{
		(*i)->run();
	}
}

PlayerCamera *GameScene::createPlayerCam(const vector3df &position, const vector3df &rotation)
{
	PlayerCamera *ret = new PlayerCamera(graphics, position, rotation);
	return ret;
}