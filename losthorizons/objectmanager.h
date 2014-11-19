#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include "itemproperties.h"
#include "shipproperties.h"
#include "turretproperties.h"
#include "spacestationproperties.h"
#include "planetproperties.h"
#include "fighterproperties.h"

//load all objects from xml files
//let's index each part of the vector for constant access time and to make it easier on us

class ObjectManager
{
public:
	ObjectManager();
	~ObjectManager();
	
	//enum of all items in the game
	//position in the enum should relate to the index
	// this will eventually be rewritten to support adding in new items without
	// having to add code and recompile the game
	// that will be necessary if we want this game to be easily modded
	enum E_ITEM_LIST
	{
		WATER,
		IRIDIUM,
		NANOALLOYS,
		RAILGUNI,	//weapons should start here for organization
		HYDRAI,
		ANTIMATTERI,
		GATLINGI,
		PHOTONI,
		PLASMAI,
		//number of items
		ITEM_COUNT
	};
	enum E_SHIP_LIST
	{
		PRAE_CRUISER,
		ISHTAR_CRUISER,
		EAGLE_FREIGHTER
	};
	enum E_FIGHTER_LIST
	{
		DRAGONFLY,
	};
	enum E_PLANET_LIST
	{
		ARGREA,
		FARSTAR,
	};
	enum E_STATION_LIST
	{
		TRADING,
		SHIPYARD
	};
	
	static std::vector<ItemProperties*> itemList;
	static std::vector<ShipProperties*> shipList;
	static std::vector<FighterProperties*> fighterList;
	static std::vector<PlanetProperties*> planetList;
	static std::vector<SpaceStationProperties*> stationList;
};

#endif
