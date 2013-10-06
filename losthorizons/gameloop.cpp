//#include "stdafx.h"
#include "gameloop.h"


Gameloop::Gameloop(IrrlichtDevice *graphics, KeyListener *receiver, DataManager *data)
	: graphics(graphics), receiver(receiver), data(data), gameSceneManager(new GameSceneManager(graphics)),
	  objectManager(new ObjectManager(graphics)), playerCam(0), hud(0), turning(0), visualsManager(new VisualsManager), 
	  missionManager(new MissionManager), stationMenu(0), gameMenu(0), intercom(0)
{
}

Gameloop::~Gameloop()
{
	//clear everything we created
	delete objectManager;
	delete gameSceneManager;
	delete missionManager;
	delete player;
	delete hud;
	delete intercom;
	delete turning;
	delete visualsManager;
	delete stationMenu;
	delete gameMenu;
}

void Gameloop::init()
{
	//create super important objects
	playerCam = gameSceneManager->getCurrentScene()->createPlayerCam(vector3df(500.f,500.f,500.f));
	hud = new HUD(player);
	intercom = new Intercom(player);
	turning = new TurningMarker(player);
	stationMenu = new StationMenu(player);
	gameMenu = new GameMenu(player);
	missionManager->addMission(MissionProperties(graphics, "missions/tutorial.xml"));
}

void Gameloop::run(f32 frameDeltaTime)
{
	//run through all essential objects and functions
	playerControl(frameDeltaTime);
	cameraControl();
	selectTarget();
	playerCam->run(player->getPosition(), frameDeltaTime); 
	gameSceneManager->runCurrentScene(frameDeltaTime);
	hud->run();
	intercom->run();
	turning->run();
	visualsManager->run();
	missionManager->run();
	stationMenu->run(player->getShipTarget());
	gameMenu->run();
}

void Gameloop::createNewGame()
{
	//create player and camera
	gameSceneManager->changeCurrentScene(SCENE_TAU_CETI);
	TargetableObject::nextID = 0;
	//create player ship
	gameSceneManager->getCurrentScene()->createShip(FACTION_TERRAN);
	//temporary for testing purposes only
	gameSceneManager->getCurrentScene()->createShip(FACTION_TERRAN,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(500,0,0));
	gameSceneManager->getCurrentScene()->createShip(FACTION_TERRAN,
		ObjectManager::E_SHIP_LIST::PRAE_CRUISER, vector3df(-500,0,0));
	gameSceneManager->getCurrentScene()->createShip(FACTION_PIRATE,
		ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(500,0,2000));
	gameSceneManager->getCurrentScene()->createShip(FACTION_PIRATE,
		ObjectManager::E_SHIP_LIST::ISHTAR_CRUISER, vector3df(-1000,0,2300));
	gameSceneManager->getCurrentScene()->createStation(FACTION_TERRAN,
		ObjectManager::E_STATION_LIST::TRADING, vector3df(1000, 0, 500));
	gameSceneManager->getCurrentScene()->createStation(FACTION_TERRAN,
		ObjectManager::E_STATION_LIST::SHIPYARD, vector3df(2000, -100, -2000));
	init();
}

void Gameloop::createLoadedGame(const std::string &filename)
{
	data->load(filename);
}// plan to get rid of this and just do things from the savemenu class

void Gameloop::playerControl(f32 frameDeltaTime)
{
	//all actions the player can do are stored here
	if (receiver->isKeyDown(irr::KEY_KEY_X) && !player->getInfo().warping) {
		//accelerate
		player->increaseVelocity(frameDeltaTime);
	} else if (receiver->isKeyDown(irr::KEY_KEY_Z)&& !player->getInfo().warping) {
		//decelerate
		player->decreaseVelocity(frameDeltaTime);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_A)&& !player->getInfo().warping) {
		//rotate left
		vector3df rot = player->getTargetRotation();
		rot.Y -= 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D)&& !player->getInfo().warping) {
		//rotate right
		vector3df rot = player->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_W)&& !player->getInfo().warping) {
		//rotate up
		vector3df rot = player->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S)&& !player->getInfo().warping) {
		//rotate down
		vector3df rot = player->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		player->setTargetRotation(rot);
	}
	if (receiver->isKeyDown(irr::KEY_SPACE)) {
		player->fireTurrets();
		intercom->addText(L"Firing all available batteries sir!");
	}
	//do docking
	if (receiver->isKeyReleased(irr::KEY_KEY_V))
	{
		if(!player->getInfo().docked)
		{
			player->dockWithTarget();
			//make sure the menu only shows up when the player is actually docked
			if(player->getInfo().docked)
			{
				stationMenu->setVisible(true);
				intercom->addText(L"Yes sir, aligning ship to dock with station");
			}
			else
			{
				//did not dock
				intercom->addText(L"Sir, we are too far away to dock with that station");
			}
		}
		else
		{
			player->undockWithTarget();
			stationMenu->setVisible(false);
		}
	}
	//draw command console
	if (receiver->isKeyReleased(irr::KEY_KEY_C))
	{
		if(gameMenu->getVisible())
		{
			gameMenu->setVisible(false);
		}
		else
		{
			gameMenu->setVisible(true);
		}
	} 
	//launch fighters
	if (receiver->isKeyReleased(irr::KEY_KEY_N))
	{
		player->launchFighters();
		intercom->addText(L"Launching available fighters, sir");
	}
	if (receiver->isKeyReleased(irr::KEY_KEY_J))
	{
		player->warpToTarget();
		intercom->addText(L"Yes sir, initiating warp sequence");
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
	if (receiver->getLeftMouseButton() && !stationMenu->getVisible()) {
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
