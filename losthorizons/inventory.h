#ifndef _INVENTORY_H_
#define _INVENTORY_H_


#include <vector>
#include <map>

#include "objectmanager.h"
#include "itemproperties.h"


//cargo for each ship
//we make this a seperate class
class Inventory
{
public:
	//constructor
	Inventory();
	//parameterized constructor
	Inventory(int credits);
	~Inventory();
	
	//overload arthimetic operators
	Inventory& operator+=(const Inventory& rhs);

	//overloaded function
	void addItem(ObjectManager::E_ITEM_LIST itemType);
	//we can use this function to add multiple copies of one object
	void addItem(ObjectManager::E_ITEM_LIST itemType, unsigned amount);
	//use this when we have the itemproperties from another object
	void addItem(const ItemProperties &item, unsigned amount);

	//overloaded function
	void removeItem(ObjectManager::E_ITEM_LIST itemType);

	//overload the subscript operator
	const unsigned getItemCount(ObjectManager::E_ITEM_LIST itemType);
	const unsigned operator[](unsigned i) const;

	//depreciated
	//return rvalue
	//const std::vector<ItemProperties*> getItemPropertiesPtr() const;

	//use this for displaying the inventory in a store or cargo display
	//we have two functions that are used for inventories!
	//one to indicate how much quantity the player has, the other to remove the 0s in between the data so we can select without issues
	std::vector<std::wstring> getConvertedInventory() const;
	//this returns all the items that have a count > 0
	std::vector<ObjectManager::E_ITEM_LIST> getConvertedInventoryNoSpaces() const;
	//depreciated
	std::vector<std::wstring> getWeaponsList() const;
	//we need several more vectors from this so we can do weapon swapping
	std::vector<ObjectManager::E_ITEM_LIST> getMediumWeapons() const;
	std::vector<ObjectManager::E_ITEM_LIST> getLightWeapons() const;

	const int getCredits() const;
	void addCredits(int modifier);
protected:
	//each index corresponds to an item
	std::vector<unsigned> data;
	//store ship credits too
	int credits;
};

inline Inventory operator+(Inventory lhs, const Inventory& rhs)
{
	lhs += rhs;
	return lhs;
}

#endif
