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
	for(std::list<Object*>::iterator i = objectsList.begin(); i != objectsList.end(); i++)
	{
		(*i)->run();
	}
}