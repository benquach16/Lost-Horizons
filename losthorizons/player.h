#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ship.h"
#include "hud.h"
#include "commandcontextmenu.h"
#include "intercom.h"
#include "minimap.h"
#include "turningmarker.h"
#include "playercamera.h"
#include "gamemenu.h"
#include "stationmenu.h"
#include "rearmmenu.h"
#include "fleet.h"

//allow the player to switch between 3 modes for different things
enum E_PLAYER_COMMAND_MODE
{
	MODE_TACTICAL,
	MODE_NAVIGATION,
	MODE_COMMAND
};

// TODO: the player class needs to be reworked so that the game doesn't
// crash when the player's ship is destroyed
// i recommend we make the player a separate entity from his ship
// that simply gets attached to whatever he is controlling
// the player could simply be the camera
// this method also has the added advantage of making it super easy to
// swap out the player's ship
class Player
{
public:
	Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Player(const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation);
	virtual ~Player();
	void run();
	
	const E_PLAYER_COMMAND_MODE getCurrentMode() const;
	Ship* getShip();
	void setShip(Ship *ship);
private:
	RearmMenu *rearmMenu;
	E_PLAYER_COMMAND_MODE currentMode;
	Ship *ship;
	void init();
	void control();
	void playerCommandFleet();
	void playerOrderShip(unsigned i, int order);
	//automate collsion handling
	bool getPickedPoint(vector3df& position);

	bool shootReleased;

	HUD *hud;
	Minimap *minimap;
	Intercom *intercom;
	TurningMarker *turning;
	PlayerCamera *playerCam;
	scene::IMeshSceneNode *grid;
	CommandContextMenu commandMenu;

	//ui members
	GameMenu *gameMenu;
	StationMenu *stationMenu;
};

#endif
