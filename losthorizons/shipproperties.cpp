//#include "stdafx.h"
#include "shipproperties.h"
#include <iostream>

ShipProperties::ShipProperties() : ModelProperties()
{
}

ShipProperties::ShipProperties(IrrlichtDevice *graphics, const std::string &f) : ModelProperties(graphics, f)
{
	//only read the ship values here since the item one will already be read in from
	//read in the xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());


	while(file->read())
	{

		//ship stats now
		if(core::stringw(L"shipStats").equals_ignore_case(file->getNodeName()))
		{
			hull = file->getAttributeValueAsInt(L"hull");
			maxVelocity = file->getAttributeValueAsFloat(L"maxVelocity");
			maxTurn = file->getAttributeValueAsInt(L"maxTurn");

			maxEnergy = file->getAttributeValueAsInt(L"maxEnergy");
			maxCrew = file->getAttributeValueAsInt(L"maxCrew");

			maxHeavyTurrets = file->getAttributeValueAsInt(L"maxHeavyTurrets");
			maxMediumTurrets = file->getAttributeValueAsInt(L"maxMediumTurrets");
			maxLightTurrets = file->getAttributeValueAsInt(L"maxLightTurrets");
			maxPDTurrets = file->getAttributeValueAsInt(L"maxPDTurrets");

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

const float& ShipProperties::getMaxVel() const
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

