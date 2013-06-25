//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver)
	: graphics(graphics), objectManager(new ObjectManager(graphics)), receiver(receiver),
	  currentScene(new GameScene(graphics)), then(static_cast<float>(graphics->getTimer()->getTime()))
{
	//create player and camera
	playerCam = currentScene->createPlayerCam();
	player = currentScene->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));
}

Gameloop::~Gameloop()
{
	delete objectManager;
	delete currentScene;
}

bool Gameloop::run()
{
	//calculate the delta time
	const float now = static_cast<float>(graphics->getTimer()->getTime());
	const float frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	playerControl();
	cameraControl();
	playerCam->run(player->getPosition(), frameDeltaTime);
	currentScene->run(frameDeltaTime);

	if (receiver->isKeyDown(irr::KEY_ESCAPE)) {
		return false;
	} else {
		return true;
	}
}

void Gameloop::playerControl()
{
	//all actions the player can do are stored here
	if(receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate
	}
	else if(receiver->isKeyDown(irr::KEY_KEY_Z))
	{
		//decelerate
	}
}

void Gameloop::cameraControl()
{
	if(receiver->getRightMouseButton())
	{
		//we can rotate the camera around this way
		playerCam->rotateX(receiver->getMouseX());
		playerCam->rotateY(receiver->getMouseY());
	}
	
}
