//#include "stdafx.h"
#include "objectmanager.h"
#include <iostream>

std::vector<ItemProperties*> ObjectManager::itemList;
std::vector<ShipProperties*> ObjectManager::shipList;
std::vector<FighterProperties*> ObjectManager::fighterList;
std::vector<PlanetProperties*> ObjectManager::planetList;
std::vector<SpaceStationProperties*> ObjectManager::stationList;

ObjectManager::ObjectManager(IrrlichtDevice *graphics)
{
	//read in items and ships
	//heres the list of items and ships so far
	//would prefer not to use pointers but since there are inherited classes we have to
	std::cout << "Loading item properties...." << std::endl;
	itemList.push_back(new ItemProperties(graphics, "items/water.xml"));
	itemList.push_back(new ItemProperties(graphics, "items/iridium.xml"));
	itemList.push_back(new ItemProperties(graphics, "items/nanoalloys.xml"));
	itemList.push_back(new TurretProperties(graphics, "items/turrets/railgunI.xml"));
	itemList.push_back(new TurretProperties(graphics, "items/turrets/antimatterI.xml"));
	itemList.push_back(new TurretProperties(graphics, "items/turrets/gatlingI.xml"));
	itemList.push_back(new TurretProperties(graphics, "items/turrets/photonI.xml"));
	shipList.push_back(new ShipProperties(graphics, "items/ships/praetorian_cruiser.xml"));
	shipList.push_back(new ShipProperties(graphics, "items/ships/ishtar_cruiser.xml"));
	fighterList.push_back(new FighterProperties(graphics, "items/fighters/dragonfly.xml"));
	planetList.push_back(new PlanetProperties(graphics, "items/planets/argrea.xml"));
	planetList.push_back(new PlanetProperties(graphics, "items/planets/farstar.xml"));
	stationList.push_back(new SpaceStationProperties(graphics, "items/spacestations/tradingstation.xml"));
	stationList.push_back(new SpaceStationProperties(graphics, "items/spacestations/shipyard.xml"));
}

ObjectManager::~ObjectManager()
{

}
