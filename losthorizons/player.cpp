#include "player.h"

Player::Player(E_GAME_FACTIONS faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: Ship(faction, shipType, position, rotation, true)
{
}

Player::Player(const ShipInformation &info, const vector3df &position, const vector3df &rotation)
	: Ship(info, position, rotation, true)
{
}

Player::~Player()
{
}

void Player::run(f32 frameDeltaTime)
{
	Ship::run(frameDeltaTime);
}
