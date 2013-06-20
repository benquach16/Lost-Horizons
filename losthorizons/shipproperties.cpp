//#include "stdafx.h"
#include "shipproperties.h"

ShipProperties::ShipProperties(IrrlichtDevice *graphics, const std::string &f) : ItemProperties(graphics, f)
{
	//only read the ship values here since the item one will already be read in from
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());


	while(file)
	{


		if(file->getNodeName() == L"modelStats")
		{
			filename = file->getAttributeValue(L"filename");
			diffuseMap = file->getAttributeValue(L"diffuseMap");
			normalMap = file->getAttributeValue(L"normalMap");

			scale.X = file->getAttributeValueAsFloat(L"scaleX");
			scale.Y = file->getAttributeValueAsFloat(L"scaleY");
			scale.Z = file->getAttributeValueAsFloat(L"scaleZ");


		}

		//ship stats now
		if(file->getNodeName() == L"shipStats")
		{
			hull = file->getAttributeValueAsInt(L"hull");
			maxVelocity = file->getAttributeValueAsInt(L"maxVelocity");
			maxTurn = file->getAttributeValueAsInt(L"maxTurn");

			maxFighters = file->getAttributeValueAsInt(L"maxFighters");
		}
	}

	file->drop();
}
