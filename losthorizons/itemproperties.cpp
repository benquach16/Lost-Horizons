//#include "stdafx.h"
#include "itemproperties.h"
#include <iostream>

ItemProperties::ItemProperties(irr::IrrlichtDevice *graphics, const std::string &f)
{
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	while(file)
	{
		//from itemstats block
		if(file->getNodeName() == L"itemStats")
		{
			itemType = getItemType(file->getAttributeValue(L"type"));

			name = file->getAttributeValue(L"name");
			description = file->getAttributeValue(L"description");

			price = file->getAttributeValueAsInt(L"cost");
			weight = file->getAttributeValueAsInt(L"weight");
		}
		
	}

	file->drop();
}

ItemProperties::~ItemProperties()
{
}

E_ITEM_TYPES ItemProperties::getItemType(const std::wstring &str)
{
	//private conversion function
	if(str == L"item")
	{
		return E_ITEM;
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
