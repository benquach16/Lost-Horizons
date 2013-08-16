#include "stdafx.h"
#include "turningmarker.h"

TurningMarker::TurningMarker(Player *player) : player(player)
{
}

TurningMarker::~TurningMarker()
{
}

void TurningMarker::run()
{
	//make sure to orient everything correctly
	XYcircle->setPosition(player->getPosition());
	YZcircle->setPosition(player->getPosition());
	arrow->setPosition(player->getPosition());
}
