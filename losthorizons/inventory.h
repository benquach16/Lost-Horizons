#ifndef _INVENTORY_H_
#define _INVENTORY_H_


#include <vector>
#include <map>

#include "objectmanager.h"


//cargo for each ship
//we make this a seperate class
class Inventory
{
public:
	//constructor
	Inventory();
	~Inventory();
	//copy constructor
	Inventory(const Inventory& i);
	//overloaded assignment operator
	Inventory& operator=(const Inventory& i);

	void addItem(ObjectManager::E_ITEM_LIST itemType);

	void removeItem(ObjectManager::E_ITEM_LIST itemType);

	//overload the subscript operator
	const unsigned getItemCount(ObjectManager::E_ITEM_LIST itemType) const;
	const unsigned operator[](ObjectManager::E_ITEM_LIST itemType) const;

	//use this for displaying the inventory in a store or cargo display
	std::vector<std::wstring> getConvertedInventory() const;

	const int getCredits() const;
	void addCredits(int modifier);
protected:
	//load all the items in the game into an associative array
	//index in array corresponds to item index
	std::vector<unsigned> data;
	//std::map<ItemProperties, unsigned> data;
	//store ship credits too
	int credits;
};

#endif
