#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "ship.h"
#include "hud.h"
#include "intercom.h"
#include "minimap.h"
#include "turningmarker.h"
#include "playercamera.h"
#include "gamemenu.h"
#include "stationmenu.h"
#include "fleet.h"

//allow the player to switch between 3 modes for different things
enum E_PLAYER_COMMAND_MODE
{
	MODE_TACTICAL,
	MODE_NAVIGATION,
	MODE_COMMAND
};

class Player : public Ship
{
public:
	Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation);
	Player(const ShipInformation &info, const s8 *subsystems, const vector3df &position, const vector3df &rotation);
	virtual ~Player();
	virtual bool run();
	virtual const E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const;
	
	const E_PLAYER_COMMAND_MODE getCurrentMode() const;
private:
	E_PLAYER_COMMAND_MODE currentMode;

	void init();
	void control();
	void playerCommandFleet();
	bool shootReleased;

	HUD *hud;
	Minimap *minimap;
	Intercom *intercom;
	TurningMarker *turning;
	PlayerCamera *playerCam;
	scene::IMeshSceneNode *grid;

	//ui members
	GameMenu *gameMenu;
	StationMenu *stationMenu;
};

#endif
