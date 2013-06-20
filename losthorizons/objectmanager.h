#ifndef _OBJECTMANAGER_H_
#define _OBJECTMANAGER_H_

#include <vector>
#include "irrlicht.h"
#include "itemproperties.h"
#include "shipproperties.h"


//load all objects from xml files

using namespace irr;
using namespace io;

class ObjectManager
{
public:
	ObjectManager(IrrlichtDevice *graphics);
	~ObjectManager();

	
private:
	std::vector<ItemProperties*> itemList;
};

#endif
