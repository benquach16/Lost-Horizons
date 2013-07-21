#ifndef _ITEMPROPERTIES_H_
#define _ITEMPROPERTIES_H_

#include <string>
#include "irrlicht.h"

using namespace irr;
using namespace io;

//so we can call specific parts of the item
enum E_ITEM_TYPES
{
	E_ITEM_SHIP = 0,
	E_ITEM_TURRET = 1,
	E_ITEM_MODULE = 2,
	E_ITEM = 3,
	E_ITEM_PLANET = 4,
};

class ItemProperties
{
public:
	ItemProperties();
	ItemProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	virtual ~ItemProperties();

	const std::wstring& getName() const;
	const std::wstring& getDesc() const;
	const int& getPrice() const;
	const int& getWeight() const;
	const E_ITEM_TYPES& getItemType() const;

protected:
	//converter function
	E_ITEM_TYPES getItemType(const std::wstring &str);
	std::wstring name;
	std::wstring description;

	int price;
	int weight;

	E_ITEM_TYPES itemType;
};

#endif
