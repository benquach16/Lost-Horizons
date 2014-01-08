#include "stdafx.h"
#include "player.h"
#include "globals.h"

using namespace base;

Player::Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: Ship(faction, shipType, position, rotation), hud(new HUD), intercom(new Intercom), turning(new TurningMarker), minimap(new Minimap),
	  playerCam(0), gameMenu(0), stationMenu(0), shootReleased(true)
{
	init();
}

Player::Player(const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation)
	: Ship(0, info, subsystems, position, rotation), hud(new HUD), intercom(new Intercom), turning(new TurningMarker), minimap(new Minimap),
	  playerCam(0), gameMenu(0), stationMenu(0), shootReleased(true)
{
	init();
}

Player::~Player()
{
	delete hud;
	delete minimap;
	delete intercom;
	delete turning;
	delete gameMenu;
	delete stationMenu;
}

bool Player::run()
{
	control();

	hud->run(this);
	minimap->run();
	if (info.shield < 10) 
	{
		intercom->postMessage(L"Sir, our shields are down");
	}
	
	intercom->run();
	turning->run(getPosition(), getRotation(), getTargetRotation());
	playerCam->run(getPosition());
	gameMenu->run();
	stationMenu->run(shipTarget);
	
	if (shipTarget) {
		//make the ship's target have a square around it
		vdriver->draw2DImage(vdriver->getTexture("res/menu/target.png"), shipTarget->getScreenPosition() - vector2di(32), rect<s32>(0,0,64,64), 0, video::SColor(255,255,255,255), true);
		//add cool lines
		vdriver->draw2DLine(vector2d<s32>(shipTarget->getScreenPosition().X, 0), vector2d<s32>(shipTarget->getScreenPosition().X, height), video::SColor(128,128,128,140));
		vdriver->draw2DLine(vector2d<s32>(0, shipTarget->getScreenPosition().Y), vector2d<s32>(width, shipTarget->getScreenPosition().Y), video::SColor(128,128,128,140));

		//move turret aim lines to here so only player has them
		for(unsigned i = 0; i < mediumTurrets.size(); i++)
		{
			//draw pretty lines here
			if(mediumTurrets[i]->getCanFire())
			{
				/*
				vdriver->setTransform(video::ETS_WORLD, core::matrix4());
				vdriver->draw3DLine(mediumTurrets[i]->getPosition(),
					shipTarget->getPosition(), video::SColor(255,0,255,0));	
					*/
				//2d line is a temporary fix
				//becaause with postprocessing enabled, 3d lines do not work!!!!!!
				vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(mediumTurrets[i]->getPosition());
				vector2di i = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getAlteredShipPosition());
				vdriver->draw2DLine(t, i, video::SColor(255,0,255,0));
			}
		}
		for(unsigned i = 0; i < lightTurrets.size(); i++)
		{
			if(lightTurrets[i]->getCanFire())
			{
				/*
				//draw pretty lines here
				vdriver->setTransform(video::ETS_WORLD, core::matrix4());
				vdriver->draw3DLine(lightTurrets[i]->getPosition(),
					shipTarget->getPosition(), video::SColor(255,0,255,0));	
					*/
			}
		}
	}
	return Ship::run();
}

const E_TARGETABLEOBJECT_TYPE Player::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_PLAYER;
}

void Player::init()
{
	game->setPointers(this, intercom);
	playerCam = game->getGameSceneManager()->createPlayerCam(vector3df(500.f,500.f,500.f));
	gameMenu = new GameMenu(this);
	stationMenu = new StationMenu(this);
	shipFleet = new Fleet;
	shipFleet->addShipToFleet(this);
}

void Player::control()
{



	//all actions the player can do are stored here
	if (receiver->isKeyPressed(KEY_LBUTTON) && !gameMenu->getVisible() && !stationMenu->getVisible()) {
		//do target selection code here
		setTarget(0);
		unsigned i = 0;
		while (!getShipTarget() && i < TargetableObject::allTargets.size()) {
			//see if there's a square here
			const int x = receiver->getMouseX() - TargetableObject::allTargets[i]->getScreenPosition().X;
			const int y = receiver->getMouseY() - TargetableObject::allTargets[i]->getScreenPosition().Y;
			if (TargetableObject::allTargets[i]->getTargetable() && (x*x + y*y) < 1024) {
				setTarget(TargetableObject::allTargets[i]);
			}
			i++;
		}
	}
	if (receiver->isKeyDown(irr::KEY_KEY_X) && !info.warping) {
		//accelerate
		increaseVelocity();
	} else if (receiver->isKeyDown(irr::KEY_KEY_Z)&& !info.warping) {
		//decelerate
		decreaseVelocity();
	}
	if (receiver->isKeyDown(irr::KEY_KEY_A)&& !info.warping) {
		//rotate left
		setTargetRotation(getTargetRotation() - core::vector3df(0,35*frameDeltaTime,0));
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D)&& !info.warping) {
		//rotate right
		vector3df rot = getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		setTargetRotation(getTargetRotation() + core::vector3df(0,35*frameDeltaTime,0));
	}
	if (receiver->isKeyDown(irr::KEY_KEY_W)&& !info.warping) {
		//rotate up
		vector3df rot = getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		setTargetRotation(getTargetRotation() - core::vector3df(35*frameDeltaTime,0,0));
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S)&& !info.warping) {
		//rotate down
		vector3df rot = getTargetRotation();
		rot.X += 35*frameDeltaTime;
		setTargetRotation(getTargetRotation() + core::vector3df(35*frameDeltaTime,0,0));
	}
	if (receiver->isKeyDown(irr::KEY_SPACE) && shootReleased) 
	{
		fireTurrets();
		intercom->postMessage(L"Firing all available batteries sir!");
		shootReleased = false;
	}
	else if (receiver->isKeyUp(irr::KEY_SPACE))
	{
		shootReleased = true;
	}
	//lets use the 1-4 keys for stuff like ship abilities
	//do docking
	if (receiver->isKeyReleased(irr::KEY_KEY_V))
	{
		if(!info.docked)
		{
			dockWithTarget();
			//make sure the menu only shows up when the player is actually docked
			if(info.docked)
			{
				stationMenu->setVisible(true);
				intercom->postMessage(L"Yes sir, aligning ship to dock with station");
			}
			else
			{
				//did not dock
				intercom->postMessage(L"Sir, we are too far away to dock with that station");
			}
		}
		else
		{
			undockWithTarget();
			stationMenu->setVisible(false);
		}
	}
	//draw command console
	if (receiver->isKeyReleased(irr::KEY_KEY_C))
	{
		gameMenu->setVisible(!gameMenu->getVisible());
	}
	//launch fighters
	if (receiver->isKeyReleased(irr::KEY_KEY_N))
	{
		launchFighters();
		intercom->postMessage(L"Launching available fighters, sir");
	}
	if (receiver->isKeyReleased(irr::KEY_KEY_J))
	{
		warpToTarget();
		intercom->postMessage(L"Yes sir, initiating warp sequence");
	}
	if(receiver->isKeyReleased(irr::KEY_MINUS))
	{
		minimap->zoomOut();
	}
	if(receiver->isKeyReleased(irr::KEY_PLUS))
	{
		minimap->zoomIn();
	}
	if(receiver->isKeyReleased(irr::KEY_KEY_M))
	{
		minimap->enlarge();
	}
	if(receiver->isKeyDown(irr::KEY_NUMPAD8))
	{
		info.shieldDirection = SHIELD_FORE;
	}	
	else if(receiver->isKeyDown(irr::KEY_NUMPAD4))
	{
		info.shieldDirection = SHIELD_PORT;
	}
	else if(receiver->isKeyDown(irr::KEY_NUMPAD6))
	{
		info.shieldDirection = SHIELD_STARBOARD;
	}

}
