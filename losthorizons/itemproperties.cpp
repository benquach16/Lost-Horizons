#include "itemproperties.h"
#include "globals.h"
#include <iostream>
#include <sstream>

using namespace base;

ItemProperties::ItemProperties(const std::string &f)
{
	//read in the xml file
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
	core::stringw currentSection(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				//reading stuff that has node data
				if(currentSection.equals_ignore_case(L"name"))
				{
					name = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"description"))
				{
					description = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"cost"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> price;
				}
				if(currentSection.equals_ignore_case(L"weight"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> weight;
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				//grab the item type
				if(core::stringw(L"itemStats").equals_ignore_case(file->getNodeName()))
				{
					itemType = getItemType(file->getAttributeValue(L"type"));
				}
				if(core::stringw(L"name").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"name";
				}
				if(core::stringw(L"description").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"description";
				}
				if(core::stringw(L"cost").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"cost";
				}
				if(core::stringw(L"weight").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"weight";
				}
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				currentSection=L"";
				break;
			}
		}
	}
	file->drop();
}

ItemProperties::~ItemProperties()
{
}

const std::wstring& ItemProperties::getName() const
{
	return name;
}

const std::wstring& ItemProperties::getDesc() const
{
	return description;
}

const int& ItemProperties::getPrice() const
{
	return price;
}

const int& ItemProperties::getWeight() const
{
	return weight;
}

const E_ITEM_TYPE& ItemProperties::getItemType() const
{
	return itemType;
}

//private function
E_ITEM_TYPE ItemProperties::getItemType(const std::wstring &str)
{
	//private conversion function
	if(str == L"item")
	{
		return ITEM_CARGO;
	}
	else if(str == L"turret")
	{
		return ITEM_TURRET;
	}
	else if(str == L"module")
	{
		return ITEM_MODULE;
	}
	else if(str == L"ship")
	{
		return ITEM_SHIP;
	}
	else if(str == L"planet")
	{
		return ITEM_PLANET;
	}
	else if(str == L"fighter")
	{
		return ITEM_FIGHTER;
	}
	else
	{
		//something broke here
		std::cerr << "Error reading from item file";
		std::exit(1);
	}
}
