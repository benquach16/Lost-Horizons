#include "stdafx.h"
#include "gameloop.h"

Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener receiver) : currentScene(new GameScene)
{
	//create player and camera
	playerCam = graphics->getSceneManager()->addCameraSceneNode();
}

void Gameloop::run()
{
	currentScene->run();
	playerControl();
	cameraControl();
}

void Gameloop::playerControl()
{
	//all actions the player can do are stored here
	if(receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate

	}
}

void Gameloop::cameraControl()
{
	
}
