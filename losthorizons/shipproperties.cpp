//#include "stdafx.h"
#include "shipproperties.h"

ShipProperties::ShipProperties(IrrlichtDevice *graphics, const std::string &filename) : ItemProperties(graphics, filename)
{
	//only read the ship values here since the item one will already be read in from
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(filename.c_str());

	while(file)
	{
		//from itemstats block
		if(file->getNodeName() == L"modelStats")
		{

		}
		
	}

	file->drop();
}
