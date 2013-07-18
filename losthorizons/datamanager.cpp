#include "stdafx.h"
#include "datamanager.h"
#include <fstream>

DataManager::ShipData& operator<<(DataManager::ShipData& shipData, const Ship *s)
{
	shipData.position = s->getPosition();
	shipData.rotation = s->getRotation();
	shipData.info = s->getShipInfo();
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
std::ofstream& operator<<(std::ofstream& ofs, std::stack<T>& s)
{
	ofs << u32(s.size());
    while (!s.empty()) {
		ofs << s.top();
		s.pop();
	}
    return ofs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, T& t)
{
    ifs.read((char*)&t, sizeof(t));
    return ifs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, std::stack<T>& s)
{
	u32 size;
	ifs >> size;
	T tmp;
    for (unsigned i = 0; i < size; ++i) {
		ifs >> tmp;
		s.push(tmp);
	}
    return ifs;
}

void DataManager::pull()
{
	scene = game->getGameSceneManager()->getCurrentScene()->getScene();
	ShipData tmp;
	ships.push(tmp << game->getPlayer());
	for (std::list<Ship*>::iterator i = Ship::allShips.begin(); i!= Ship::allShips.end(); ++i)
		ships.push(tmp << *i);
}

void DataManager::push()
{
	game->getGameSceneManager()->changeCurrentScene(scene);
	//construct ships
	//pop ships
}

void DataManager::save(const std::string &filename)
{
	pull();
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	ofs << scene << ships;
	ofs.close();
}

void DataManager::load(const std::string &filename)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);
	ifs >> scene >> ships;
	ifs.close();
	push();
}
