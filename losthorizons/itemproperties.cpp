//#include "stdafx.h"
#include "itemproperties.h"
#include <iostream>
#include <sstream>

ItemProperties::ItemProperties()
{
}

ItemProperties::ItemProperties(irr::IrrlichtDevice *graphics, const std::string &f)
{
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
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

//private function
E_ITEM_TYPES ItemProperties::getItemType(const std::wstring &str)
{
	//private conversion function
	if(str == L"item")
	{
		return E_ITEM;
	}
	else if(str == L"turret")
	{
		return E_ITEM_TURRET;
	}
	else if(str == L"module")
	{
		return E_ITEM_MODULE;
	}
	else if(str == L"ship")
	{
		return E_ITEM_SHIP;
	}
	else
	{
		//something broke here
		std::cerr << "Error reading from item file";
		std::exit(1);
	}
}
