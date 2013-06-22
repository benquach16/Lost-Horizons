//#include "stdafx.h"
#include "shipproperties.h"
#include <iostream>

ShipProperties::ShipProperties(IrrlichtDevice *graphics, const std::string &f) : ItemProperties(graphics, f)
{
	//only read the ship values here since the item one will already be read in from
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());


	while(file->read())
	{


		if(core::stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
		{
			filename = file->getAttributeValue(L"filename");
			diffuseMap = file->getAttributeValue(L"diffuseMap");
			normalMap = file->getAttributeValue(L"normalMap");

			scale.X = file->getAttributeValueAsFloat(L"scaleX");
			scale.Y = file->getAttributeValueAsFloat(L"scaleY");
			scale.Z = file->getAttributeValueAsFloat(L"scaleZ");


		}

		//ship stats now
		if(core::stringw(L"shipStats").equals_ignore_case(file->getNodeName()))
		{
			hull = file->getAttributeValueAsInt(L"hull");
			maxVelocity = file->getAttributeValueAsInt(L"maxVelocity");
			maxTurn = file->getAttributeValueAsInt(L"maxTurn");

			maxFighters = file->getAttributeValueAsInt(L"maxFighters");
		}
	}

	file->drop();
}

ShipProperties::~ShipProperties()
{
}

//accessors
const int& ShipProperties::getHull() const
{
	return hull;
}
const int& ShipProperties::getMaxTurn() const
{
	return maxTurn;
}

const int& ShipProperties::getMaxVel() const
{
	return maxVelocity;
}

const int& ShipProperties::getMaxEnergy() const
{
	return maxEnergy;
}
const int& ShipProperties::getMaxCrew() const
{
	return maxCrew;
}

const int& ShipProperties::getMaxLTurrets() const
{
	return maxLightTurrets;
}
const int& ShipProperties::getMaxMTurrets() const
{
	return maxMediumTurrets;
}
const int& ShipProperties::getMaxHTurrets() const
{
	return maxHeavyTurrets;
}
const int& ShipProperties::getMaxPTurrets() const
{
	return maxPDTurrets;
}

const std::wstring& ShipProperties::getFilename() const
{
	return filename;
}
const std::wstring& ShipProperties::getDiffuseMap() const
{
	return diffuseMap;
}
const std::wstring& ShipProperties::getNormalMap() const
{
	return normalMap;
}

const core::vector3df& ShipProperties::getScale() const
{
	return scale;
}
