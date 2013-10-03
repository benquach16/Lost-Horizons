#ifndef _ITEMPROPERTIES_H_
#define _ITEMPROPERTIES_H_

#include <string>
#include "irrlicht.h"

using namespace irr;
using namespace io;

//so we can call specific parts of the item
enum E_ITEM_TYPE
{
	ITEM_CARGO,
	ITEM_SHIP,
	ITEM_TURRET,
	ITEM_MODULE,
	ITEM_PLANET,
	ITEM_FIGHTER
};


//itemproperties class
//all items need this class
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
	const E_ITEM_TYPE& getItemType() const;

protected:
	//converter function
	E_ITEM_TYPE getItemType(const std::wstring &str);
	std::wstring name;
	std::wstring description;

	int price;
	int weight;

	E_ITEM_TYPE itemType;
};

//overload == operator
inline bool operator==(const ItemProperties& lhs, const ItemProperties& rhs)
{
	if(lhs.getDesc() == rhs.getDesc() && lhs.getName() == rhs.getName() && lhs.getItemType() == rhs.getItemType() &&
		lhs.getPrice() == rhs.getPrice() && lhs.getWeight() == rhs.getWeight())
	{
		return true;
	}
	return false;
}


#endif
