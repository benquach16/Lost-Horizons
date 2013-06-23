//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver) : 
	currentScene(new GameScene(graphics)), objectManager(new ObjectManager(graphics)),
	graphics(graphics), receiver(receiver), then(graphics->getTimer()->getTime())
{
	//create player and camera
	currentScene->createPlayerCam();
	currentScene->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));

}

Gameloop::~Gameloop()
{
}

void Gameloop::run()
{
	//calculate the delta time
	const float now = graphics->getTimer()->getTime();
	const float frameDeltaTime = (f32)(now - then) / 1000.f; // Time in seconds
	then = now;

	playerControl();
	currentScene->run();
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

