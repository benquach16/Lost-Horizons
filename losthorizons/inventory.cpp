#include "inventory.h"


Inventory::Inventory()
{
	//load items into data structor
	for(unsigned i = 0; i < ObjectManager::itemList.size(); i++)
	{
		data.push_back(0);
	}
}

Inventory::~Inventory()
{
}

Inventory::Inventory(const Inventory& i)
{
}

Inventory& Inventory::operator=(const Inventory& i)
{
	return *this;
}

void Inventory::addItem(ObjectManager::E_ITEM_LIST itemType)
{
	//itemtype should be aligned with array index
	data[itemType] ++;
}

void Inventory::removeItem(ObjectManager::E_ITEM_LIST itemType)
{
	//make sure we dont accidently increase the number to the maximum unsigned value
	if(data[itemType] > 0)
		data[itemType] --;
}

const unsigned Inventory::getItemCount(ObjectManager::E_ITEM_LIST itemType) const
{
	return data[itemType];
}

const unsigned Inventory::operator[](ObjectManager::E_ITEM_LIST itemType) const
{
	return data[itemType];
}

std::vector<std::wstring> Inventory::getConvertedInventory() const
{
	//create an array where we remove the elements that don't need to be there
	//and stack items
	std::vector<std::wstring> ret;
	for(unsigned i = 0; i < data.size(); i++)
	{
		if(data[i] > 0)
		{
			std::wstring tmp = ObjectManager::itemList[i].getName();
			tmp += L" x";
			tmp += std::to_wstring(data[i]);
			ret.push_back(tmp);
		}
	}
	return ret;
}

const int Inventory::getCredits() const
{
	return credits;
}

void Inventory::addCredits(int modifier)
{
	credits += modifier;
}
