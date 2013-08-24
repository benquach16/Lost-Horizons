#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include "irrlicht.h"
#include "itemproperties.h"
#include "shipproperties.h"
#include "turretproperties.h"
#include "planetproperties.h"


//load all objects from xml files

using namespace irr;
using namespace io;

//lets index each part of the vector for constant access time and to make it easier on us


class ObjectManager
{
public:
	ObjectManager(IrrlichtDevice *graphics);
	~ObjectManager();
	
	//enum of all items in the game
	//position in the enum should relate to the index
	enum E_ITEM_LIST
	{
		WATER,
	};	
	enum E_SHIP_LIST
	{
		PRAE_CRUISER,
		ISHTAR_CRUISER,
	};
	enum E_TURRET_LIST
	{
		RAILGUNI,
		ANTIMATTERI,
	};
	enum E_PLANET_LIST
	{
		ARGREA,
		FARSTAR,
	};
	
	static std::vector<ItemProperties> itemList;
	static std::vector<ShipProperties> shipList;
	static std::vector<TurretProperties> turretList;
	static std::vector<PlanetProperties> planetList;
};

#endif
