#include "inventory.h"


Inventory::Inventory()
{
	//load items into data structor
	for(unsigned i = 0; i < ObjectManager::itemList.size(); i++)
	{
		data.push_back(0);
	}
	for(unsigned i = 0; i < ObjectManager::turretList.size(); i++)
	{
		data.push_back(0);
	}
}

Inventory::~Inventory()
{
}
