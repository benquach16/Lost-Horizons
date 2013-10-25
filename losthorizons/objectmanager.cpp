#include "stdafx.h"
#include "objectmanager.h"
#include <iostream>

std::vector<ItemProperties*> ObjectManager::itemList;
std::vector<ShipProperties*> ObjectManager::shipList;
std::vector<FighterProperties*> ObjectManager::fighterList;
std::vector<PlanetProperties*> ObjectManager::planetList;
std::vector<SpaceStationProperties*> ObjectManager::stationList;

ObjectManager::ObjectManager()
{
	//read in items and ships
	//heres the list of items and ships so far
	//would prefer not to use pointers but since there are inherited classes we have to
	std::cout << "Loading item properties...." << std::endl;
	itemList.push_back(new ItemProperties("items/water.xml"));
	itemList.push_back(new ItemProperties("items/iridium.xml"));
	itemList.push_back(new ItemProperties("items/nanoalloys.xml"));
	itemList.push_back(new TurretProperties("items/turrets/railgunI.xml"));
	itemList.push_back(new TurretProperties("items/turrets/antimatterI.xml"));
	itemList.push_back(new TurretProperties("items/turrets/gatlingI.xml"));
	itemList.push_back(new TurretProperties("items/turrets/photonI.xml"));
	shipList.push_back(new ShipProperties("items/ships/praetorian_cruiser.xml"));
	shipList.push_back(new ShipProperties("items/ships/ishtar_cruiser.xml"));
	fighterList.push_back(new FighterProperties("items/fighters/dragonfly.xml"));
	planetList.push_back(new PlanetProperties("items/planets/argrea.xml"));
	planetList.push_back(new PlanetProperties("items/planets/farstar.xml"));
	stationList.push_back(new SpaceStationProperties("items/spacestations/tradingstation.xml"));
	stationList.push_back(new SpaceStationProperties("items/spacestations/shipyard.xml"));
}

ObjectManager::~ObjectManager()
{
	for (unsigned i = 0; i < itemList.size(); ++i)
		delete itemList[i];
	itemList.clear();
	for (unsigned i = 0; i < shipList.size(); ++i)
		delete shipList[i];
	shipList.clear();
	for (unsigned i = 0; i < fighterList.size(); ++i)
		delete fighterList[i];
	fighterList.clear();
	for (unsigned i = 0; i < planetList.size(); ++i)
		delete planetList[i];
	planetList.clear();
	for (unsigned i = 0; i < stationList.size(); ++i)
		delete stationList[i];
	stationList.clear();
}
