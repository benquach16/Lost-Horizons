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
	TargetableObject::nextID = 0;
	player = gameSceneManager->getCurrentScene()->createPlayer(E_FACTION_TERRAN);
	//temporary for testing purposes only
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_NEUTRAL,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0));
	hud = new HUD(player);
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
	delete hud;
}

void Gameloop::run()
{
	//calculate the delta time
	const f32 now = (f32)(graphics->getTimer()->getTime());
	const f32 frameDeltaTime = (now-then)/1000.f; // Time in seconds
	then = now;

	playerControl(frameDeltaTime);
	cameraControl();
	selectTarget();
	playerCam->run(player->getPosition(), frameDeltaTime);
	gameSceneManager->runCurrentScene(frameDeltaTime);
	hud->run();
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
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_W))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S))
	{
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		player->setTargetRotation(rot);
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

void Gameloop::selectTarget()
{
	//do target selection code here
	if(receiver->getLeftMouseButton())
	{
		//see if theres a square here
		for(std::list<TargetableObject*>::iterator i = TargetableObject::allTargets.begin(); i != TargetableObject::allTargets.end(); i++)
		{
			const int x = receiver->getMouseX() - (*i)->getScreenPosition().X;
			const int y = receiver->getMouseY() - (*i)->getScreenPosition().Y;
			if(((x*x)+(y*y)) < 1024)
			{
				player->setTarget(*i);
				return;
			}
		}
		player->setTarget(0);
		return;
	}
}
