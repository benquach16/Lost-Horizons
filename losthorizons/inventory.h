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
	void addItem(ObjectManager::E_TURRET_LIST turretType, unsigned amount);
	//use this when we have the itemproperties from another object
	void addItem(const ItemProperties &item, unsigned amount);

	//overloaded function
	void removeItem(ObjectManager::E_ITEM_LIST itemType);
	//O(1) time remove function
	void removeItem(int i);

	//overload the subscript operator
	const unsigned getItemCount(ObjectManager::E_ITEM_LIST itemType);
	const ItemProperties& operator[](unsigned i) const;

	//use this for displaying the inventory in a store or cargo display
	std::vector<std::wstring> getConvertedInventory() const;
	std::vector<std::wstring> getWeaponsList() const;

	const int getCredits() const;
	void addCredits(int modifier);
protected:
	//we have two vectors to act as an associative array;
	//make sure these two vectors are always in SYNC!!!
	//we could use one vector with std::pair, but that would cause needless, needless pain
	//this is much faster and easier
	std::vector<ItemProperties> data;
	std::vector<unsigned> count;
	//std::vector<ItemProperties, unsigned> data;
	//std::map<ItemProperties, unsigned> data;
	//store ship credits too
	int credits;
};

inline Inventory operator+(Inventory lhs, const Inventory& rhs)
{
	lhs += rhs;
	return lhs;
}

#endif
