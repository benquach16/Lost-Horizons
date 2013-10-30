#include "stdafx.h"
#include "player.h"
#include "globals.h"

using namespace base;

Player::Player(const E_GAME_FACTION faction, const ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: Ship(faction, shipType, position, rotation)
{
	game->setPlayer(this);
}

Player::Player(const ShipInformation &info, const std::vector<s8> &subsystems, const vector3df &position, const vector3df &rotation)
	: Ship(0, info, subsystems, position, rotation)
{
	game->setPlayer(this);
}

Player::~Player()
{
}

void Player::run(f32 frameDeltaTime)
{
	Ship::run(frameDeltaTime);
	//do player specific stuff
	if (shipTarget) {
		//make the ship's target have a square around it
		vdriver->draw2DImage(vdriver->getTexture("res/menu/target.png"), shipTarget->getScreenPosition() - vector2di(32), rect<s32>(0,0,64,64), 0, video::SColor(255,255,255,255), true);
		//add cool lines
		vdriver->draw2DLine(vector2d<s32>(shipTarget->getScreenPosition().X, 0), vector2d<s32>(shipTarget->getScreenPosition().X, height), video::SColor(128,128,128,140));
		vdriver->draw2DLine(vector2d<s32>(0, shipTarget->getScreenPosition().Y), vector2d<s32>(width, shipTarget->getScreenPosition().Y), video::SColor(128,128,128,140));
	}
}

const E_TARGETABLEOBJECT_TYPE Player::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_PLAYER;
}
