#include "stdafx.h"
#include "cargo.h"
#include "globals.h"

using namespace base;

const int SPINSPEED = 10;
const int MAXMONEY = 10000;

Cargo::Cargo(const vector3df &position, const bool randomizeContents)
	: TargetableObject(L"Cargo Container", L"", L"res/models/equipment/loot.3DS", position, vector3df(), vector3df(1,1,1), FACTION_NEUTRAL)
{
	setTexture(vdriver->getTexture("res/models/equipment/lootcan1-map.png"));
	if (randomizeContents)
	{
		//self explanitory
		//make the inventory all random n shit
		inventory.addCredits(rand()%10000 + 1);
		unsigned i = rand()%ObjectManager::E_ITEM_LIST::ITEM_COUNT;
		inventory.addItem((ObjectManager::E_ITEM_LIST)i, rand()%10);
	}
}

Cargo::Cargo(const vector3df &position, const Inventory &inv)
	: TargetableObject(L"Cargo Container", L"", L"res/models/equipment/loot.3DS", position, vector3df(), vector3df(1,1,1), FACTION_NEUTRAL),
	  inventory(inv)
{
	setTexture(vdriver->getTexture("res/models/equipment/lootcan1-map.png"));
}

Cargo::~Cargo()
{
}

bool Cargo::run()
{
	//spin the container so it looks cool!
	setRotation(getRotation() + core::vector3df(0,SPINSPEED*frameDeltaTime,frameDeltaTime));
	return TargetableObject::run();
}

const E_TARGETABLEOBJECT_TYPE Cargo::getTargetableObjectType() const
{
	return TARGETABLEOBJECT_MISC;
}

Inventory& Cargo::getInventory()
{
	return inventory;
}

const Inventory& Cargo::getInventory() const
{
	return inventory;
}
