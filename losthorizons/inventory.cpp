#include "inventory.h"


Inventory::Inventory() : credits(0)
{

}

Inventory::~Inventory()
{
}

Inventory& Inventory::operator+=(const Inventory& rhs)
{
	//add inventory contents to this one
	for (unsigned i = 0; i < rhs.data.size(); ++i) {
		addItem(rhs.data[i], rhs.count[i]);
	}
	credits += rhs.credits;
	return *this;
}

void Inventory::addItem(ObjectManager::E_ITEM_LIST itemType)
{
	//itemtype should be aligned with array index
	for (unsigned i = 0; i < data.size(); ++i) {
		//we found the same one so increment the count
		if (data[i] == ObjectManager::itemList[itemType]) {
			count[i]++;
			return;
		}
	}
	//if we didnt find it add another count and itemproperty to data
	data.push_back(ObjectManager::itemList[itemType]);
	count.push_back(1);
}

void Inventory::addItem(ObjectManager::E_ITEM_LIST itemType, unsigned amount)
{
	//itemtype should be aligned with array index
	for (unsigned i = 0; i < data.size(); ++i) {
		//we found the same one so increaes count by amount
		if (data[i] == ObjectManager::itemList[itemType]) {
			count[i] += amount;
			return;
		}
	}
	//if we didnt find it add count and itemproperty to data
	data.push_back(ObjectManager::itemList[itemType]);
	count.push_back(amount);
}

void Inventory::addItem(const ItemProperties& item, unsigned amount)
{
	//itemtype should be aligned with array index
	for (unsigned i = 0; i < data.size(); ++i) {
		//we found the same one so increaes count by amount
		if (data[i] == item) {
			count[i] += amount;
			return;
		}
	}
	//if we didnt find it add count and itemproperty to data
	data.push_back(item);
	count.push_back(amount);
}


void Inventory::removeItem(ObjectManager::E_ITEM_LIST itemType)
{
	//make sure we dont accidently increase the number to the maximum unsigned value
	for (unsigned i = 0; i < data.size(); ++i) {
		if (data[i] == ObjectManager::itemList[itemType]) {
			if (count[i] > 1) {
				count[i]--;
				return;
			} else {
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
	if (count[i] > 1) {
		count[i]--;
		return;
	} else {
		data.erase(data.begin() + i);
		count.erase(count.begin() + i);
	}
}


const unsigned Inventory::getItemCount(ObjectManager::E_ITEM_LIST itemType)
{
	for(unsigned i = 0; i < data.size(); ++i) {
		if (data[i] == ObjectManager::itemList[itemType]) {
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
	for (unsigned i = 0; i < data.size(); ++i)
	{
		std::wstring tmp = data[i].getName();
		tmp += L" x";
		tmp += std::to_wstring(count[i]);
		ret.push_back(tmp);
	}
	return ret;
}

std::vector<std::wstring> Inventory::getWeaponsList() const
{
	std::vector<std::wstring> ret;
	for( unsigned i = 0; i < data.size(); ++i)
	{
		if(data[i].getItemType() == E_ITEM_TURRET)
		{
			std::wstring tmp = data[i].getName();
			tmp += L" x";
			tmp += std::to_wstring(count[i]);
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
