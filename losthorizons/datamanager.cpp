#include "stdafx.h"
#include "datamanager.h"
#include "globals.h"
#include "config.h"
#include "planet.h"
#include <fstream>

using namespace base;

DataManager::ShipData& operator<<(DataManager::ShipData& shipData, Ship *s)
{
	shipData.ID = s->getID();
	shipData.targetting = s->getShipTarget() != 0;
	if (shipData.targetting)
		shipData.target = s->getShipTarget()->getID();
	shipData.position = s->getPosition();
	shipData.rotation = s->getRotation();
	shipData.info = s->getInfo();
	shipData.subsystems = s->getSubsystems();
	return shipData;
}

/*
// if i have a string, change it into a size and a char array
string mystr = "hello world!";

// write
ofstream ofs("string.txt", ios::binary);
u32 sizea = mystr.size()+1;
char* a = new char[sizea];
strcpy(a, mystr.c_str());
ofs.write((char*)&sizea, sizeof(sizea));
ofs.write(a, sizea);
ofs.close();
delete a;

// read
ifstream ifs("string.txt", ios::binary);
u32 sizeb;
ifs.read((char*)&sizeb, sizeof(sizeb));
char* b = new char[sizeb];
ifs.read((char*)b, sizeb);
ifs.close();

mystr = b;
delete b;
*/

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, const T& t)
{
    ofs.write((char*)&t, sizeof(t));
    return ofs;
}

template <typename T>
std::ofstream& operator<<(std::ofstream& ofs, std::deque<T>& d)
{
	ofs << u16(d.size());
    while (!d.empty()) {
		ofs << d.back();
		d.pop_back();
	}
    return ofs;
}

std::ofstream& operator<<(std::ofstream& ofs, const DataManager::ShipData& shipData)
{
	ofs << shipData.ID << shipData.target << shipData.targetting << shipData.position << shipData.rotation << shipData.info;
	for (u32 i = 0; i < SUBSYSTEM_COUNT; ++i)
		ofs << shipData.subsystems[i];
    return ofs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, T& t)
{
    ifs.read((char*)&t, sizeof(t));
    return ifs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, std::deque<T>& d)
{
	u16 size;
	ifs >> size;
	T tmp;
    for (u16 i = 0; i < size; ++i) {
		ifs >> tmp;
		d.push_front(tmp);
	}
    return ifs;
}

std::ifstream& operator>>(std::ifstream& ifs, DataManager::ShipData& shipData)
{
    ifs >> shipData.ID >> shipData.target >> shipData.targetting >> shipData.position >> shipData.rotation >> shipData.info;
	shipData.subsystems.resize(SUBSYSTEM_COUNT);
	for (u32 i = 0; i < SUBSYSTEM_COUNT; ++i)
		ifs >> shipData.subsystems[i];
    return ifs;
}

void DataManager::pull()
{
	if (gConfig.bPlay) {
		scene = game->getGameSceneManager()->getCurrentScene();
		for (std::list<Planet*>::iterator i = Planet::allPlanets.begin(); i != Planet::allPlanets.end(); ++i)
			(*i)->removeThisFromTargets();
		ShipData tmp;
		for (unsigned i = 0; i < Ship::allShips.size(); i++) 
			ships.push_front(tmp << Ship::allShips[i]);
	}
}

void DataManager::push()
{
	if (gConfig.bPlay) {
		game->getGameSceneManager()->destroyScene();
		game->getGameSceneManager()->changeCurrentScene(scene);
		while (!ships.empty()) {
			game->getGameSceneManager()->createShip(ships.front().ID, ships.front().info, ships.front().subsystems, ships.front().position, ships.front().rotation);
			shipTargets.push(std::pair<bool,u16>(ships.front().targetting, ships.front().target));
			ships.pop_front();
		}
		setShipTargets();
		game->init();
	}
}

void DataManager::save(const std::string &filename)
{
	pull();
	CreateDirectory(L".\\saves", NULL);
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	ofs << scene << TargetableObject::nextID << ships;
	ofs.close();
}

void DataManager::load(const std::string &filename)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);
	ifs >> scene >> TargetableObject::nextID >> ships;
	ifs.close();
	push();
}

void DataManager::setShipTargets()
{
	u32 size = TargetableObject::allTargets.size()/3;
	targets = new std::list<TargetableObject*>[size];
	for (unsigned i = 0; i < TargetableObject::allTargets.size(); i++) {
		targets[TargetableObject::allTargets[i]->getID()%size].push_front(TargetableObject::allTargets[i]);
	}
	for (unsigned i = 0; i < TargetableObject::allTargets.size(); i++)
	{
		if (shipTargets.top().first)
		{
			std::list<TargetableObject*>::iterator j = targets[shipTargets.top().second%size].begin();
			while ((*j)->getID() != shipTargets.top().second)
				j++;
			Ship::allShips[i]->setTarget(*j);
		}
		shipTargets.pop();
	}
	delete[] targets;
}
