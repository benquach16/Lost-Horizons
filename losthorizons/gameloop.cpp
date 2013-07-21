//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver, DataManager *data)
	: graphics(graphics), receiver(receiver), data(data), gameSceneManager(new GameSceneManager(graphics)),
	  objectManager(new ObjectManager(graphics)), then((f32)(graphics->getTimer()->getTime()))
{
	//player = gameSceneManager->getCurrentScene()->createPlayer(ObjectManager::shipList[0], vector3df(0,0,0), vector3df(0,0,0));	
}

void Gameloop::createNewGame()
{
	//create player and camera
	gameSceneManager->changeCurrentScene(E_TAU_CETI_SCENE);
	playerCam = gameSceneManager->getCurrentScene()->getCurrentSceneCamera();
	player = gameSceneManager->getCurrentScene()->createPlayer(E_FACTION_TERRAN);
	//temporary for testing purposes only
	player->setTarget(gameSceneManager->getCurrentScene()->createShip(E_FACTION_NEUTRAL,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0)));
}

void Gameloop::createLoadedGame(const std::string &filename)
{
	data->load(filename);
}// plan to get rid of this and just do things from the savemenu class

Gameloop::~Gameloop()
{
	delete objectManager;
	delete gameSceneManager;
	delete player;
}

void Gameloop::run()
{
	//calculate the delta time
	const f32 now = (f32)(graphics->getTimer()->getTime());
	const f32 frameDeltaTime = (now-then)/1000.f; // Time in seconds
	then = now;

	playerControl(frameDeltaTime);
	cameraControl();
	playerCam->run(player->getPosition(), frameDeltaTime);
	gameSceneManager->runCurrentScene(frameDeltaTime);
}

void Gameloop::playerControl(f32 frameDeltaTime)
{
	//all actions the player can do are stored here
	if (receiver->isKeyDown(irr::KEY_KEY_X))
	{
		//accelerate
		player->increaseVelocity(frameDeltaTime);
	}
	else if (receiver->isKeyDown(irr::KEY_KEY_Z))
	{
		//decelerate
		player->decreaseVelocity(frameDeltaTime);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_A))
	{
		//rotate left
		vector3df rot = player->getTargetRotation();
		rot.Y -= 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_W))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		player->setTargetRotationTo(rot);
	}
	if(receiver->isKeyDown(irr::KEY_SPACE))
	{
		player->fireTurrets();
	}
}

void Gameloop::cameraControl()
{
	if (receiver->getRightMouseButton())
	{
		//we can rotate the camera around this way
		playerCam->rotateX(receiver->getMouseX());
		playerCam->rotateY(receiver->getMouseY());
	}
	playerCam->zoom(receiver->getMouseWheel());
}
