#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

#include "irrlicht.h"
#include "itemproperties.h"
//items are all objects that does not have to be 3d
//all objects are items but not all items are objects

class Item
{
public:
	Item(); 
	Item(const ItemProperties &itemProps);
	virtual ~Item();
protected:
	std::wstring name;
	std::wstring description;
	int cost;
	int weight;
};

#endif
