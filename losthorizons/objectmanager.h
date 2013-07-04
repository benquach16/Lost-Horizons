#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include "irrlicht.h"
#include "itemproperties.h"
#include "shipproperties.h"
#include "turretproperties.h"


//load all objects from xml files

using namespace irr;
using namespace io;

//lets index each part of the vector for constant access time and to make it easier on us


class ObjectManager
{
public:
	ObjectManager(IrrlichtDevice *graphics);
	~ObjectManager();

	enum E_ITEM_LIST
	{
		WATER = 0,
	};	
	enum E_SHIP_LIST
	{
		PRAE_CRUISER = 0,
	};
	
	static std::vector<ItemProperties> itemList;
	static std::vector<ShipProperties> shipList;
	static std::vector<TurretProperties> turretList;
	
};

#endif
