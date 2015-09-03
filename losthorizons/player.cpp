#include "stdafx.h"
#include "player.h"
#include "globals.h"
#pragma hdrstop

using namespace base;

Player::Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: ship(new Ship(faction, shipType, position, rotation)), hud(new HUD), intercom(new Intercom), turning(new TurningMarker), minimap(new Minimap),
	playerCam(0), gameMenu(0), stationMenu(0), shootReleased(true), currentMode(MODE_TACTICAL)
{

	init();
	hud->initializePlayerShipsInFleet(ship->getFleet());
	rearmMenu = new RearmMenu;
	rearmMenu->loadFleet(this->ship->getFleet());
}

Player::Player(const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation)
	: ship(new Ship(0, info, subsystems, position, rotation)), hud(new HUD), intercom(new Intercom), turning(new TurningMarker), minimap(new Minimap),
	  playerCam(0), gameMenu(0), stationMenu(0), shootReleased(true), currentMode(MODE_TACTICAL)
{
	init();
	hud->initializePlayerShipsInFleet(ship->getFleet());
	rearmMenu = new RearmMenu;
	rearmMenu->loadFleet(this->ship->getFleet());
}

Player::~Player()
{
	delete hud;
	delete minimap;
	delete intercom;
	delete turning;
	delete gameMenu;
	delete stationMenu;
	grid->remove();
}
void Player::run()
{
	// let's make the player invinvible until we can get some bugs sorted out
	// until the console can enable godmode, it'll be done like this
	rearmMenu->run();
	if(ship)
	{
		//if (ship->getInfo().armor < 1000) ship->info.armor = 427912304;
		// I'M FUXXING INVINCIBLE
		vector3df position = ship->getPosition();
		vector3df rotation = ship->getRotation();
		vector3df scale = ship->getScale();
		const TargetableObject *shipTarget = ship->getShipTarget();
		if(currentMode == MODE_COMMAND)
		{
			//allow player ro command fleet
			playerCommandFleet();
			hud->setFleetVisible(true);
			hud->updatePlayerShipsInFleet(ship->getFleet());
			grid->setVisible(true);
		}
		else
		{
			grid->setVisible(false);
			hud->setFleetVisible(false);
		}

		control();
		hud->run(ship);

		minimap->run();
		if (ship->getInfo().shield < 10) 
		{
			intercom->postMessage(L"Sir, our shields are down");
		}

		intercom->run();
		turning->run(position, rotation, ship->getTargetRotation());
		playerCam->run(position);
		if (gameMenu->getVisible()) 
		{
			gameMenu->run();
		}
		if (stationMenu->getVisible() && shipTarget && shipTarget->getTargetableObjectType() == TARGETABLEOBJECT_SPACESTATION) 
		{
			stationMenu->setTarget((TargetableObject*)shipTarget); //UGLY HACK TO GET AROUND CONST LOL
			stationMenu->run();
		}
		//is this a good way of implementing it?
		for(unsigned i = 1; i < ship->getFleet()->size(); i++)
		{
			vdriver->draw2DImage(vdriver->getTexture("res/menu/target_array_friendly.png"),
				ship->getFleet()->getShipsInFleet()[i]->getScreenPosition() - vector2di(16),
				rect<s32>(0,0,32,32), 0,
				video::SColor(255,255,255,255), true);
		}

		if (shipTarget) 
		{
			if(!shipTarget->getActive())
			{
				shipTarget = 0;
				return;
			}
			//make the ship's target have a square around it
			vdriver->draw2DImage(vdriver->getTexture("res/menu/target.png"), shipTarget->getScreenPosition() - vector2di(32), rect<s32>(0,0,64,64), 0, video::SColor(255,255,255,255), true);
			//add cool lines

			vdriver->draw2DLine(vector2d<s32>(shipTarget->getScreenPosition().X, 0), vector2d<s32>(shipTarget->getScreenPosition().X, height), video::SColor(128,128,128,140));
			vdriver->draw2DLine(vector2d<s32>(0, shipTarget->getScreenPosition().Y), vector2d<s32>(width, shipTarget->getScreenPosition().Y), video::SColor(128,128,128,140));
			/*
			//move turret aim lines to here so only player has them
			for(unsigned i = 0; i < ship->getTurrets(TURRET_MEDIUM).size(); i++)
			{

				//draw pretty lines here
				if(ship->getTurrets(TURRET_MEDIUM)[i]->getCanFire())
				{

					//vdriver->setTransform(video::ETS_WORLD, core::matrix4());
					//vdriver->draw3DLine(mediumTurrets[i]->getPosition(),
					//shipTarget->getPosition(), video::SColor(255,0,255,0));	

					//2d line is a temporary fix
					//becaause with postprocessing enabled, 3d lines do not work!!!!!!
					if(shipTarget->getScreenPosition().X > 1&& shipTarget->getScreenPosition().Y > 1)
					{
						vector3df temp = ship->getTurrets(TURRET_MEDIUM)[i]->getPosition();
						vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(temp);
						vdriver->draw2DImage(vdriver->getTexture("res/menu/target.png"), t, rect<s32>(0,0,64,64), 0, video::SColor(255,255,255,255), true);
						vector2di i = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(vector3df(0,0,0));

						vdriver->draw2DLine(t, i, video::SColor(255,100,255,100));
					}
				}
			}
			*/
		
			
			//allow ship commands to go here
			if(receiver->isKeyDown(irr::KEY_F1))
			{
				currentMode = MODE_TACTICAL;
			}
			else if(receiver->isKeyDown(irr::KEY_F2))
			{
				currentMode = MODE_NAVIGATION;
			}
			else if(receiver->isKeyDown(irr::KEY_F3))
			{
				currentMode = MODE_COMMAND;
			}
		}
	}
}



const E_PLAYER_COMMAND_MODE Player::getCurrentMode() const
{
	return currentMode;
}

Ship* Player::getShip()
{
	return ship;
}

//private functions
void Player::init()
{
	game->setPointers(this, intercom);
	playerCam = game->getGameSceneManager()->createPlayerCam(vector3df(500.f,500.f,500.f));
	gameMenu = new GameMenu(ship);
	stationMenu = new StationMenu(ship);
	Fleet *shipFleet = new Fleet;
	ship->addToFleet(shipFleet);
	shipFleet->addShipToFleet(ship);

	//need to initialize command grid
	grid = scenemngr->addCubeSceneNode();
	grid->setMaterialTexture(0,vdriver->getTexture("res/menu/grid.png"));
	grid->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	grid->setMaterialFlag(video::EMF_LIGHTING, false);
	grid->setScale(vector3df(1000,0.1f,1000));
	grid->getMaterial(0).getTextureMatrix(0).setTextureScale(10,10);
	grid->setVisible(false);

	scene::ITriangleSelector *selector = scenemngr->createTriangleSelector(grid->getMesh(), grid);
	grid->setTriangleSelector(selector);
	selector->drop();

}

void Player::control()
{
	//all actions the player can do are stored here
	if (receiver->isKeyPressed(KEY_LBUTTON) && !gameMenu->getVisible() && !stationMenu->getVisible()) 
	{
		//do target selection code here
		ship->setTarget(0);
		unsigned i = 0;
		while (!ship->getShipTarget() && i < TargetableObject::allTargets.size()) 
		{
			//see if there's a square here
			const int x = receiver->getMouseX() - TargetableObject::allTargets[i]->getScreenPosition().X;
			const int y = receiver->getMouseY() - TargetableObject::allTargets[i]->getScreenPosition().Y;
			if (TargetableObject::allTargets[i]->getTargetable() && (x*x + y*y) < 1024) 
			{
				ship->setTarget(TargetableObject::allTargets[i]);
			}
			i++;
		}
	}
	if (receiver->isKeyDown(irr::KEY_KEY_X) && !ship->getInfo().warping) 
	{
		//accelerate
		ship->increaseVelocity();
	} 
	else if (receiver->isKeyDown(irr::KEY_KEY_Z)&& !ship->getInfo().warping) 
	{
		//decelerate
		ship->decreaseVelocity();
	}
	if (receiver->isKeyDown(irr::KEY_KEY_A)&& !ship->getInfo().warping) 
	{
		//rotate left
		ship->setTargetRotation(ship->getTargetRotation() - core::vector3df(0,35*frameDeltaTime,0));
	}
	if (receiver->isKeyDown(irr::KEY_KEY_D)&& !ship->getInfo().warping) 
	{
		//rotate right
		vector3df rot = ship->getTargetRotation();
		rot.Y += 35*frameDeltaTime;
		ship->setTargetRotation(ship->getTargetRotation() + core::vector3df(0,35*frameDeltaTime,0));
	}
	//DISABLE ROTATE UP AND DOWN FOR NOW CAUSE ITS NOT INTUITIVE
	/*
	if (receiver->isKeyDown(irr::KEY_KEY_W)&& !ship->getInfo().warping) 
	{
		//rotate up
		vector3df rot = ship->getTargetRotation();
		rot.X -= 35*frameDeltaTime;
		ship->setTargetRotation(ship->getTargetRotation() - core::vector3df(35*frameDeltaTime,0,0));
	}
	if (receiver->isKeyDown(irr::KEY_KEY_S)&& !ship->getInfo().warping) 
	{
		//rotate down
		vector3df rot = ship->getTargetRotation();
		rot.X += 35*frameDeltaTime;
		ship->setTargetRotation(ship->getTargetRotation() + core::vector3df(35*frameDeltaTime,0,0));
	}
	*/
	if (receiver->isKeyReleased(irr::KEY_SPACE)) 
	{
		ship->fireTurrets();
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
		if(!ship->getInfo().docked)
		{
			ship->dockWithTarget();
			//make sure the menu only shows up when the player is actually docked
			if(ship->getInfo().docked)
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
			ship->undockWithTarget();
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
		ship->launchFighters();
		intercom->postMessage(L"Launching available fighters, sir");
	}
	if (receiver->isKeyReleased(irr::KEY_KEY_J))
	{
		ship->warpToTarget();
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
		ship->setShieldDirection(SHIELD_FORE);
	}	
	else if(receiver->isKeyDown(irr::KEY_NUMPAD4))
	{
		ship->setShieldDirection(SHIELD_PORT);
	}
	else if(receiver->isKeyDown(irr::KEY_NUMPAD6))
	{
		ship->setShieldDirection(SHIELD_STARBOARD);
	}
	else if(receiver->isKeyDown(irr::KEY_NUMPAD5))
	{
		ship->setShieldDirection(SHIELD_NULL);
	}


}

void Player::playerCommandFleet()
{
	//draw command sphere
	grid->setPosition(ship->getPosition());
	//this gets alittle tricky to do intuitively
	//make sure we highlight all of the player's subordinate ships
	//player should always be head of fleet
	Fleet *shipFleet = ship->getFleet();
	for(unsigned i = 1; i < shipFleet->getShipsInFleet().size(); i++)
	{
		//lets try to color our ships
		//and display their stats on the menu
		//shipFleet->getShipsInFleet()[i]->highlightShip();
		if(shipFleet->getShipsInFleet()[i]->getShipTarget())
		{
			//it if has a target
			
			vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(
				shipFleet->getShipsInFleet()[i]->getPosition());
			vector2di v = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(
				shipFleet->getShipsInFleet()[i]->getShipTarget()->getPosition());
					
			vdriver->draw2DLine(t, v, video::SColor(255,255,122,122));
		}
		if(shipFleet->getShipsInFleet()[i]->getInfo().currentAIOrder == ORDER_MOVETOLOCATION ||
			shipFleet->getShipsInFleet()[i]->getInfo().currentAIOrder == ORDER_ATTACKANDMOVE)
		{
			vector2di t = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(
				shipFleet->getShipsInFleet()[i]->getPosition());
			vector2di v = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(
				shipFleet->getShipsInFleet()[i]->getInfo().orderMove);
					
			vdriver->draw2DLine(t, v, video::SColor(255,122,122,255));
		}
		if(shipFleet->getShipsInFleet()[i] == ship->getShipTarget())
		{
			//if player targeted it we're ready to give orders
			vdriver->draw2DLine(vector2d<s32>(receiver->getMouseX(), 0), vector2d<s32>(receiver->getMouseX(), height), video::SColor(128,128,150,255));
			vdriver->draw2DLine(vector2d<s32>(0, receiver->getMouseY()), vector2d<s32>(width, receiver->getMouseY()), video::SColor(128,128,150,255));
			//just allow us to give move orders for now
			if(receiver->isKeyPressed(irr::KEY_RBUTTON))
			{
				commandMenu.setVisible(true);
			}
			if(receiver->isKeyPressed(irr::KEY_LBUTTON) && commandMenu.getVisible())
			{
				playerOrderShip(i, commandMenu.getSelected());
			}
			//shortcut hotkeys go here
			if(receiver->isKeyPressed(irr::KEY_KEY_1))
			{
				playerOrderShip(i, 0);
			}
			else if(receiver->isKeyPressed(irr::KEY_KEY_2))
			{
				playerOrderShip(i, 1);
			}
			else if(receiver->isKeyPressed(irr::KEY_KEY_3))
			{
				// attack target hotkey
				// right now its kinda a hacky method
				playerOrderShip(i, 2);
				
			}
			else if(receiver->isKeyPressed(irr::KEY_KEY_4))
			{
			}
			else if(receiver->isKeyPressed(irr::KEY_KEY_5))
			{
				playerOrderShip(i, 4);
			}
			else if(receiver->isKeyPressed(irr::KEY_KEY_6))
			{
				playerOrderShip(i, 5);
			}
		}
	}
}

void Player::playerOrderShip(unsigned i, int order)
{
	Fleet *shipFleet = ship->getFleet();
	switch(order)
	{
		case 0:
		{

			// move to this locaation hotkey
			//calculate intersection between plane and ray

			vector3df position;
			if(getPickedPoint(position))
				shipFleet->getShipsInFleet()[i]->giveOrderMove(vector3df(position.X,grid->getPosition().Y,position.Z));
			break;
		}
		case 1:
		{

			// general attack hotkey
			vector3df position;
			if(getPickedPoint(position))
				shipFleet->getShipsInFleet()[i]->giveOrderAttackGeneral(vector3df(position.X,grid->getPosition().Y,position.Z));
			break;
		}
		case 2:
		{
			//this is not a particularly fun method
			vector3df position;
			if(getPickedPoint(position))
			{
				for(unsigned j = 0; j < Ship::allShips.size(); j++)
				{
					if(Ship::allShips[j]->getPosition().getDistanceFromSQ(position) < 400)
					{
						//pretty uglie
						shipFleet->getShipsInFleet()[i]->giveOrderAttackTarget(
							Ship::allShips[j]);
					}
				}
			}
			break;
		}
		case 3:
		{

			// move here and attack hotkey
			vector3df position;
			if(getPickedPoint(position))
				shipFleet->getShipsInFleet()[i]->giveOrderAttackAndMove(vector3df(position.X,grid->getPosition().Y,position.Z));
			break;
		}
		case 4:
		{
			shipFleet->getShipsInFleet()[i]->giveOrderFollow();
			break;
		}
		case 5:
		{
			shipFleet->getShipsInFleet()[i]->giveOrderFollowPassive();
			break;
		}
		default:
		{
			//do nothing
			break;
		}
	}
}

bool Player::getPickedPoint(vector3df& position)
{
	triangle3df tri;
	ISceneNode *node;
	core::line3df line = scenemngr->getSceneCollisionManager()->getRayFromScreenCoordinates(
		vector2d<s32>(receiver->getMouseX(), receiver->getMouseY()),
		scenemngr->getActiveCamera());
	position.Y = ship->getPosition().Y;
	return scenemngr->getSceneCollisionManager()->getCollisionPoint(line, grid->getTriangleSelector(), position, tri, node);
}
