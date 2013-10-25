#include "stdafx.h"
#include "inventory.h"


Inventory::Inventory()
	: credits(0), data(ObjectManager::ITEM_COUNT, 0)
{
}

Inventory::~Inventory()
{
}

Inventory& Inventory::operator+=(const Inventory& rhs)
{
	//add inventory contents to this one
	for (unsigned i = 0; i < rhs.data.size(); ++i) {
		addItem((ObjectManager::E_ITEM_LIST)i, rhs.data[i]);
	}
	credits += rhs.credits;
	return *this;
}

void Inventory::addItem(ObjectManager::E_ITEM_LIST itemType)
{
	data[itemType]++;
}

void Inventory::addItem(ObjectManager::E_ITEM_LIST itemType, unsigned amount)
{
	//itemtype should be aligned with array index
	data[itemType]+=amount;
}

void Inventory::addItem(const ItemProperties& item, unsigned amount)
{
	//loop to find it
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (*ObjectManager::itemList[i] == item)
		{
			data[i]+=amount;
		}
	}
}

void Inventory::removeItem(ObjectManager::E_ITEM_LIST itemType)
{
	//make sure we don't accidentally increase the number to the maximum unsigned value
	if (data[itemType] > 0)
		data[itemType]--;
}

const unsigned Inventory::getItemCount(ObjectManager::E_ITEM_LIST itemType)
{
	return data[itemType];
}

const unsigned Inventory::operator[](unsigned index) const
{
	return data[index];
}

std::vector<std::wstring> Inventory::getConvertedInventory() const
{
	//create an array where we remove the elements that don't need to be there
	//and stack items
	std::vector<std::wstring> ret;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (data[i] > 0)
		{
			std::wstring tmp = ObjectManager::itemList[i]->getName();
			tmp += L" x";
			tmp += std::to_wstring(data[i]);
			ret.push_back(tmp);
		}
	}
	return ret;
}

std::vector<ObjectManager::E_ITEM_LIST> Inventory::getConvertedInventoryNoSpaces() const
{
	std::vector<ObjectManager::E_ITEM_LIST> ret;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (data[i] > 0)
		{
			//index corresponds to enum
			ret.push_back((ObjectManager::E_ITEM_LIST)i);
		}
	}
	return ret;
}

std::vector<std::wstring> Inventory::getWeaponsList() const
{
	std::vector<std::wstring> ret;
	for (unsigned i = 0; i < data.size(); ++i)
	{
		if (ObjectManager::itemList[i]->getItemType() == ITEM_TURRET)
		{
			std::wstring tmp = ObjectManager::itemList[i]->getName();
			tmp += L" x";
			tmp += std::to_wstring(data[i]);
			ret.push_back(tmp); 
		}
	}
	return ret;
}

std::vector<ObjectManager::E_ITEM_LIST> Inventory::getMediumWeapons() const
{
	//hackish function intended to let weapon swapping be intuitive and easier
	//its not super hackish but its getting there
	std::vector<ObjectManager::E_ITEM_LIST> ret;
	for (unsigned i = 0; i < data.size(); i++)
	{
		if (ObjectManager::itemList[i]->getItemType() == ITEM_TURRET && data[i] > 0)
		{
			TurretProperties *t = (TurretProperties*)ObjectManager::itemList[i];
			if (t->getTurretClass() == TURRET_MEDIUM)
				ret.push_back((ObjectManager::E_ITEM_LIST)i);
		}
	}

	return ret;
}

std::vector<ObjectManager::E_ITEM_LIST> Inventory::getLightWeapons() const
{
	std::vector<ObjectManager::E_ITEM_LIST> ret;
	for (unsigned i = 0; i < data.size(); i++)
	{
		if (ObjectManager::itemList[i]->getItemType() == ITEM_TURRET && data[i] > 0)
		{
			TurretProperties *t = (TurretProperties*)ObjectManager::itemList[i];
			if (t->getTurretClass() == TURRET_LIGHT)
				ret.push_back((ObjectManager::E_ITEM_LIST)i);
		}		
	}
	return ret;
}

const int Inventory::getCredits() const
{
	return credits;
}

void Inventory::addCredits(int val)
{
	credits += val;
}
