//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver)
	: graphics(graphics), objectManager(new ObjectManager(graphics)), receiver(receiver),
	  currentScene(new GameScene(graphics)), then(static_cast<float>(graphics->getTimer()->getTime()))
{
	playerCam = currentScene->createPlayerCam();
	player = currentScene->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));	
}

void Gameloop::createNewGame()
{
	//create player and camera
	playerCam = currentScene->createPlayerCam();
	player = currentScene->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));
}

void Gameloop::createLoadedGame()
{
	playerCam = currentScene->createPlayerCam();
}

Gameloop::~Gameloop()
{
	delete objectManager;
	delete currentScene;
}

bool Gameloop::run()
{
	//calculate the delta time
	const float now = (float)(graphics->getTimer()->getTime());
	const float frameDeltaTime = (float)(now - then) / 1000.f; // Time in seconds
	then = now;

	playerControl(frameDeltaTime);
	cameraControl();
	playerCam->run(player->getPosition(), frameDeltaTime);
	currentScene->run(frameDeltaTime);

	if (receiver->isKeyDown(irr::KEY_ESCAPE)) {
		return false;
	} else {
		return true;
	}
}

void Gameloop::playerControl(float frameDeltaTime)
{
	//all actions the player can do are stored here
	if(receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate
		player->increaseVelocity(frameDeltaTime);
	}
	else if(receiver->isKeyDown(irr::KEY_KEY_Z))
	{
		//decelerate
		player->decreaseVelocity(frameDeltaTime);
	}
	if(receiver->isKeyDown(irr::KEY_KEY_A))
	{
		//rotate left
		vector3df rot = player->getTargetRotation();
		rot.Y -= 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if(receiver->isKeyDown(irr::KEY_KEY_D))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if(receiver->isKeyDown(irr::KEY_KEY_W))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if(receiver->isKeyDown(irr::KEY_KEY_S))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
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
