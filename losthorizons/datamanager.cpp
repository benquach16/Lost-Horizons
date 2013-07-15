#include "stdafx.h"
#include "datamanager.h"
#include <fstream>

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
std::ofstream& operator<<(std::ofstream& ofs, const std::vector<T>& v)
{
	ofs << u32(v.size());
    for (unsigned i = 0; i < v.size(); ++i)
		ofs << v[i];
    return ofs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, T& t)
{
    ifs.read((char*)&t, sizeof(t));
    return ifs;
}

template <typename T>
std::ifstream& operator>>(std::ifstream& ifs, std::vector<T>& v)
{
	u32 size;
	ifs >> size;
    for (unsigned i = 0; i < size; ++i) {
		T tmp;
		ifs >> tmp;
		v.push_back(tmp);
	}
    return ifs;
}

void DataManager::pull()
{
	scene = game->getGameSceneManager()->getCurrentScene()->getScene();
	ships.push_back(game->getPlayer()->getShipData());
	for (std::list<Ship*>::iterator i = Ship::allShips.begin(); i!= Ship::allShips.end(); i++)
		ships.push_back((*i)->getShipData());
}

void DataManager::push()
{
	game->getGameSceneManager()->changeCurrentScene(scene);
	//construct ships
	ships.clear();
}

void DataManager::save(const std::string &filename)
{
	pull();
	std::ofstream ofs(filename.c_str(), std::ios::binary);
	ofs << scene << ships;
	ofs.close();
	ships.clear();
}

void DataManager::load(const std::string &filename)
{
	std::ifstream ifs(filename.c_str(), std::ios::binary);
	ifs >> scene >> ships;
	ifs.close();
	push();
}
