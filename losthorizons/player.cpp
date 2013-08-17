#include "stdafx.h"
#include "player.h"

Player::Player(E_GAME_FACTIONS faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: Ship(faction, shipType, position, rotation)
{
	game->setPlayer(this);
}

Player::Player(const ShipInformation &info, const vector3df &position, const vector3df &rotation)
	: Ship(0, info, position, rotation)
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
		vdriver->draw2DImage(vdriver->getTexture("res/menu/target.png"), shipTarget->getScreenPosition() - vector2di(32), rect<s32>(0,0,64,64), 0, SColor(255,255,255,255), true);
	}
}
