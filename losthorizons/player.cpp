#include "player.h"

Player::Player()
{
}

Player::Player(irr::IrrlichtDevice *graphics, const ShipProperties &props, const vector3df &position, const vector3df &rotation) :
	Ship(graphics, props, position, rotation, true)
{
}

Player::~Player()
{
}

void Player::run(float frameDeltaTime)
{
	Ship::run(frameDeltaTime);
}