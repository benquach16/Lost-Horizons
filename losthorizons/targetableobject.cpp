#include "stdafx.h"
#include "targetableobject.h"
#include "globals.h"

using namespace base;

std::vector<TargetableObject*> TargetableObject::allTargets;
u16 TargetableObject::nextID(0);

TargetableObject::TargetableObject(const u16 ID, const ModelProperties& modelProps, const vector3df &position, const vector3df &rotation,
								   const E_GAME_FACTION faction)
	: Object(modelProps.getFilename().c_str(), position, rotation, modelProps.getScale()), ID(ID), name(modelProps.getName()),
	  description(modelProps.getDesc()), faction(faction), targetable(true), index(allTargets.size())
{
	allTargets.push_back(this);
}

TargetableObject::TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale, const E_GAME_FACTION faction)
		: Object(filename, position, rotation, scale), faction(faction), name(name), description(description),
		  targetable(true), index(allTargets.size())
{
	allTargets.push_back(this);
}

TargetableObject::~TargetableObject()
{
	removeThisFromTargets();
	allTargets[index] = allTargets.back();
	allTargets[index]->index = index;
	allTargets.pop_back();
}

bool TargetableObject::run()
{
	//update 2d position of this object
	screenPosition = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getPosition(), scenemngr->getActiveCamera());
	//draw a 2d target array on this object
	if (targetable) {
		vdriver->draw2DImage(vdriver->getTexture(faction == FACTION_PIRATE
			? "res/menu/target_array_enemy.png" : "res/menu/target_array.png"),
			screenPosition - vector2di(32), rect<s32>(0,0,64,64), 0, video::SColor(255,255,255,255), true);
	}
	return Object::run();
}

void TargetableObject::removeThisFromTargets()
{
	//loop thru ship list and remove this if it is a target
	for (unsigned i = 0; i < Ship::allShips.size(); i++)
		if (Ship::allShips[i]->getShipTarget() == this)
			Ship::allShips[i]->setTarget(0);
}

const u16 TargetableObject::getID() const
{
	return ID;
}

const wchar_t *TargetableObject::getName() const
{
	return name.c_str();
}

const wchar_t *TargetableObject::getDesc() const
{
	return description.c_str();
}

const wchar_t *TargetableObject::getFactionName() const
{
	switch (faction)
	{
		case FACTION_NEUTRAL:
			return L"Neutral";
		case FACTION_PIRATE:
			return L"Pirate";
		case FACTION_TERRAN:
			return L"Terran Federation";
		case FACTION_PROVIAN:
			return L"Provian Consortium";
		default:
			return L"Unknown";
	}
}

const E_GAME_FACTION TargetableObject::getFaction() const
{
	return faction;
}

const bool TargetableObject::getTargetable() const
{
	return targetable;
}

const vector2di& TargetableObject::getScreenPosition() const
{
	return screenPosition;
}
