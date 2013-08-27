#ifndef _INVENTORY_H_
#define _INVENTORY_H_


#include <vector>

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

	void addItem(const ItemProperties& item);

	void removeItem(const ItemProperties& item);

	//overload the subscript operator
	const unsigned getItemCount(const ItemProperties& item) const;
	const unsigned operator[](const ItemProperties& item) const;

	int getCredits() const;
	int addCredits(int modifier);
protected:
	//load all the items in the game into an associative array
	//index in array corresponds to item index
	std::vector<unsigned> data;
	//store ship credits too
	int credits;
};

#endif
