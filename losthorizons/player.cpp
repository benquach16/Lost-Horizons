#include "stdafx.h"
#include "player.h"

Player::Player(E_GAME_FACTIONS faction, ObjectManager::E_SHIP_LIST shipType, const vector3df &position, const vector3df &rotation)
	: Ship(faction, shipType, position, rotation),
	  targetedIcon(guienv->addImage(vdriver->getTexture("res/menu/target.png"), core::vector2d<s32>(0,0)))
{
	targetedIcon->setVisible(false);
}

Player::Player(const ShipInformation &info, const vector3df &position, const vector3df &rotation)
	: Ship(0, info, position, rotation)
{
}

Player::~Player()
{
	targetedIcon->remove();
}

void Player::run(f32 frameDeltaTime)
{
	Ship::run(frameDeltaTime);
	//do player specific stuff
	if (shipTarget) {
		//make the ship target have a square around it
		
		targetedIcon->setVisible(true);
		vector2di t(shipTarget->getScreenPosition());
		t.X -= 32;
		t.Y -= 32;
		targetedIcon->setRelativePosition(t);
	} else
		targetedIcon->setVisible(false);
}
