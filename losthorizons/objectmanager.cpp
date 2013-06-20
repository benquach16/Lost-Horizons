//#include "stdafx.h"
#include "objectmanager.h"

ObjectManager::ObjectManager(IrrlichtDevice *graphics)
{
	//read in items and ships
	//heres the list of items and ships so far
	ItemProperties *water = new ItemProperties(graphics, "items/water.xml");
	itemList.push_back(water);
}

ObjectManager::~ObjectManager()
{
	for(unsigned i = 0; i < itemList.size(); i++)
	{
		delete itemList[i];
		itemList.erase(itemList.begin()+i);
	}
}
