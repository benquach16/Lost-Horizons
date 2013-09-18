#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>

#include "irrlicht.h"
#include "itemproperties.h"
#include "shipproperties.h"
#include "turretproperties.h"
#include "spacestationproperties.h"
#include "planetproperties.h"
#include "fighterproperties.h"


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
		IRIDIUM,
		NANOALLOYS
	};	
	enum E_SHIP_LIST
	{
		PRAE_CRUISER,
		ISHTAR_CRUISER,
	};
	enum E_FIGHTER_LIST
	{
		DRAGONFLY,
	};
	enum E_TURRET_LIST
	{
		RAILGUNI,
		ANTIMATTERI,
		GATLINGI,
		PHOTONI,
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
	
	
	static std::vector<ItemProperties> itemList;
	static std::vector<ShipProperties> shipList;
	static std::vector<FighterProperties> fighterList;
	static std::vector<TurretProperties> turretList;
	static std::vector<PlanetProperties> planetList;
	static std::vector<SpaceStationProperties> stationList;
};

#endif
