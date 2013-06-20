//#include "stdafx.h"
#include "objectmanager.h"

std::vector<ItemProperties*> ObjectManager::itemList;

ObjectManager::ObjectManager(IrrlichtDevice *graphics)
{
	//read in items and ships
	//heres the list of items and ships so far
	ItemProperties *water = new ItemProperties(graphics, "items/water.xml");
	itemList.push_back(water);
	ShipProperties *cruiser = new ShipProperties(graphics, "items/ships/praetorian_cruiser.xml");
	itemList.push_back(cruiser);
}

ObjectManager::~ObjectManager()
{
	for(unsigned i = 0; i < itemList.size(); i++)
	{
		delete itemList[i];
		itemList.erase(itemList.begin()+i);
	}
}
