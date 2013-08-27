//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop()
{
}

Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver, DataManager *data)
	: graphics(graphics), receiver(receiver), data(data), gameSceneManager(new GameSceneManager(graphics)),
	  objectManager(new ObjectManager(graphics)), hud(0), turning(0), visualsManager(new VisualsManager), stationMenu(new StationMenu)
{
}

Gameloop::~Gameloop()
{
	delete objectManager;
	delete gameSceneManager;
	delete player;
	delete hud;
	delete turning;
	delete visualsManager;
	delete stationMenu;
}

void Gameloop::init()
{
	playerCam = gameSceneManager->getCurrentScene()->getCurrentSceneCamera();
	hud = new HUD(player);
	turning = new TurningMarker(player);
}

void Gameloop::run(f32 frameDeltaTime)
{

	playerControl(frameDeltaTime);
	cameraControl();
	selectTarget();
	playerCam->run(player->getPosition(), frameDeltaTime);
	gameSceneManager->runCurrentScene(frameDeltaTime);
	hud->run();
	turning->run();
	visualsManager->run();
	stationMenu->run(player->getShipTarget());
}

void Gameloop::createNewGame()
{
	//create player and camera
	gameSceneManager->changeCurrentScene(E_TAU_CETI_SCENE);
	TargetableObject::nextID = 0;
	//create player ship
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_TERRAN);
	//temporary for testing purposes only
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_TERRAN,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0));
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_TERRAN,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(-500,0,0));
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_PIRATE,
		ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(500,0,2000));
	gameSceneManager->getCurrentScene()->createShip(E_FACTION_PIRATE,
		ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(-1000,0,2300));
	gameSceneManager->getCurrentScene()->createStation(E_FACTION_TERRAN,
		ObjectManager::E_STATION_LIST::TRADING, vector3df(1000, 0, 500));
	init();
}

void Gameloop::createLoadedGame(const std::string &filename)
{
	data->load(filename);
}// plan to get rid of this and just do things from the savemenu class

void Gameloop::playerControl(f32 frameDeltaTime)
{
	//all actions the player can do are stored here
	if (receiver->isKeyDown(irr::KEY_KEY_X)) {
		//accelerate
		player->increaseVelocity(frameDeltaTime);
	} else if (receiver->isKeyDown(irr::KEY_KEY_Z)) {
		//decelerate
		player->decreaseVelocity(frameDeltaTime);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_A)) {
		//rotate left
		vector3df rot = player->getTargetRotation();
		rot.Y -= 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D)) {
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_W)) {
		//rotate up
		vector3df rot = player->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S)) {
		//rotate down
		vector3df rot = player->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_SPACE)) {
		player->fireTurrets();
	}
	//do docking
	if (receiver->isKeyReleased(irr::KEY_KEY_V))
	{
		if(!player->getInfo().docked)
		{
			player->dockWithTarget();
			stationMenu->setVisible(true);
		}
		else
		{
			player->undockWithTarget();
			stationMenu->setVisible(false);
		}
	}
}

void Gameloop::cameraControl()
{
	if (receiver->getRightMouseButton()) {
		//we can rotate the camera around this way
		playerCam->rotateX(receiver->getMouseX());
		playerCam->rotateY(receiver->getMouseY());
	} else
		playerCam->updateMousePosition(receiver->getMouseX(), receiver->getMouseY());
	playerCam->zoom(receiver->getMouseWheel());
}

void Gameloop::selectTarget()
{
	//do target selection code here
	if (receiver->getLeftMouseButton()) {
		//see if there's a square here
		for (std::list<TargetableObject*>::iterator i = TargetableObject::allTargets.begin(); i != TargetableObject::allTargets.end(); ++i) {
			const int x = receiver->getMouseX() - (*i)->getScreenPosition().X;
			const int y = receiver->getMouseY() - (*i)->getScreenPosition().Y;
			if ((x*x + y*y) < 1024) {
				player->setTarget(*i);
				return;
			}
		}
		player->setTarget(0);
		return;
	}
}
