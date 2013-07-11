//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver)
	: graphics(graphics), objectManager(new ObjectManager(graphics)), receiver(receiver),
	  gameSceneManager(new GameSceneManager(graphics)), then(static_cast<float>(graphics->getTimer()->getTime()))
{
	//player = gameSceneManager->getCurrentScene()->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));	
}

void Gameloop::createNewGame()
{
	//create player and camera
	gameSceneManager->changeCurrentScene(E_TAU_CETI_SCENE);
	playerCam = gameSceneManager->getCurrentScene()->getCurrentSceneCamera();
	player = gameSceneManager->getCurrentScene()->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));
}

void Gameloop::createLoadedGame()
{
}

Gameloop::~Gameloop()
{
	delete player;
	delete objectManager;
	delete gameSceneManager;
}

void Gameloop::run()
{
	//calculate the delta time
	const float now = (float)(graphics->getTimer()->getTime());
	const float frameDeltaTime = (float)(now - then) / 1000.f; // Time in seconds
	then = now;

	playerControl(frameDeltaTime);
	cameraControl();
	playerCam->run(player->getPosition(), frameDeltaTime);
	gameSceneManager->runCurrentScene(frameDeltaTime);
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
