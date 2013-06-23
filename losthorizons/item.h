#ifndef _ITEM_H_
#define _ITEM_H_

#include <string>

#include "irrlicht.h"
//items are all objects that does not have to be 3d
//all objects are items but not all items are objects

struct ItemTypes
{
};

class Item
{
public:
	Item(); 
	virtual ~Item();
protected:
	std::wstring name;
	std::wstring description;


};

#endif