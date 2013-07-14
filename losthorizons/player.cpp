#include "player.h"

Player::Player()
{
}

Player::Player(const ShipProperties &props, const vector3df &position, const vector3df &rotation) :
	Ship(props, position, rotation, true)
{
}

Player::~Player()
{
}

void Player::run(f32 frameDeltaTime)
{
	Ship::run(frameDeltaTime);
}
