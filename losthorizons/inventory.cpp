#include "inventory.h"


Inventory::Inventory() : credits(0)
{

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
	for(unsigned i = 0; i < data.size(); i++)
	{
		//we found the same one so increment the count
		if(data[i] == ObjectManager::itemList[itemType])
		{
			count[i]++;
			return;
		}
	}
	//if we didnt find it add another count and itemproperty to data
	data.push_back(ObjectManager::itemList[itemType]);
	count.push_back(1);
}

void Inventory::removeItem(ObjectManager::E_ITEM_LIST itemType)
{
	//make sure we dont accidently increase the number to the maximum unsigned value
	for(unsigned i = 0; i < data.size(); i++)
	{
		if(data[i] == ObjectManager::itemList[itemType])
		{
			if(count[i] > 1)
			{
				count[i]--;
				return;
			}
			else
			{
				//remove it from the list
				data.erase(data.begin() + i);
				count.erase(count.begin() + i);
				return;
			}
		}
	}
}

void Inventory::removeItem(int i)
{
	//cconstant time removal function
	if(count[i] > 1)
	{
		count[i]--;
		return;
	}
	else
	{
		data.erase(data.begin() + i);
		count.erase(count.begin() +i);
	}
}


const unsigned Inventory::getItemCount(ObjectManager::E_ITEM_LIST itemType)
{
	for(unsigned i = 0; i < data.size(); i++)
	{
		if(data[i] == ObjectManager::itemList[itemType])
		{
			return count[i];
		}
	}
	return 0;
}

const ItemProperties& Inventory::operator[](unsigned i) const
{
	return data[i];
}

std::vector<std::wstring> Inventory::getConvertedInventory() const
{
	//create an array where we remove the elements that don't need to be there
	//and stack items
	std::vector<std::wstring> ret;
	for(unsigned i = 0; i < data.size(); i++)
	{
		std::wstring tmp = data[i].getName();
		tmp += L" x";
		tmp += std::to_wstring(count[i]);
		ret.push_back(tmp);
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
