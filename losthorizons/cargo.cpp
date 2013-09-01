#include "cargo.h"

const int SPINSPEED = 10;
const unsigned MAXMONEY = 10000;

Cargo::Cargo(const vector3df &position, bool randomizeContents) : TargetableObject(L"Cargo Container", L"", L"res/models/equipment/loot.3DS",
																				   position, vector3df(), vector3df(1,1,1), E_FACTION_NEUTRAL)
{
	if(randomizeContents)
	{
		//self explanitory
		//make the inventory all random n shit
		inventory.addCredits(rand()%10000 + 1);
		unsigned i = rand()%ObjectManager::itemList.size();
		inventory.addItem(ObjectManager::itemList[i], rand()%10);
	}
}

Cargo::Cargo(const vector3df &position, const Inventory &inv) : TargetableObject(L"Cargo Container", L"", L"res/models/equipment/loot.3DS",
																				   position, vector3df(), vector3df(1,1,1), E_FACTION_NEUTRAL),
																				   inventory(inv)
{

}

Cargo::~Cargo()
{
}

void Cargo::run(f32 frameDeltaTime)
{
	//spin the container so it looks cool!
	vector3df temp = mesh->getRotation();
	temp.Y+=SPINSPEED*frameDeltaTime;
	temp.Z+=1*frameDeltaTime;

	mesh->setRotation(temp);
	TargetableObject::run(frameDeltaTime);
}

const E_TARGETABLEOBJECT_TYPE Cargo::getTargetableObjectType() const
{
	return E_OBJECT_MISC;
}

Inventory& Cargo::getInventory()
{
	return inventory;
}

const Inventory& Cargo::getInventory() const
{
	return inventory;
}
