#include "player.h"

Player::Player()
{
}

Player::Player(const vector3df &position, const vector3df &rotation, const ShipProperties &props)
	: Ship(position, rotation, true, props)
{
}

Player::~Player()
{
}

void Player::run(f32 frameDeltaTime)
{
	Ship::run(frameDeltaTime);
}
