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

	core::stringw currentSection(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"shipStats").equals_ignore_case(file->getNodeName()))
				{
					hull = file->getAttributeValueAsInt(L"hull");
					maxVelocity = file->getAttributeValueAsFloat(L"maxVelocity");
					maxTurn = file->getAttributeValueAsInt(L"maxTurn");

					maxEnergy = file->getAttributeValueAsInt(L"maxEnergy");
					maxCrew = file->getAttributeValueAsInt(L"maxCrew");

					maxPDTurrets = file->getAttributeValueAsInt(L"maxPDTurrets");

					maxFighters = file->getAttributeValueAsInt(L"maxFighters");
				}
				//we have some turret loading crap here
				if(currentSection==L"" && core::stringw(L"heavyTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"heavyTurret";
					maxHeavyTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"heavyTurret"))
				{
					//load heavy turret information
					for(unsigned i = 0; i < maxHeavyTurrets; i++)
					{
						//gotta convert the i to a string for this
						if(core::stringw(i).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsFloat(L"arc");
							heavyTurrets.push_back(tmp);
						}
					}
				}
				if(currentSection==L"" && core::stringw(L"mediumTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"mediumTurret";
					maxMediumTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"mediumTurret"))
				{
					for(unsigned i = 0; i < maxMediumTurrets; i++)
					{
						//gotta convert the i to a string for this
						if(core::stringw(i).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsFloat(L"arc");
							mediumTurrets.push_back(tmp);
						}
					}		
				}
				if(currentSection==L"" && core::stringw(L"lightTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"lightTurret";
					maxLightTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"lightTurret"))
				{
					for(unsigned i = 0; i < maxLightTurrets; i++)
					{
						//gotta convert the i to a string for this
						if(core::stringw(i).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsFloat(L"arc");
							lightTurrets.push_back(tmp);
						}
					}		
				}
				break;
			case io::EXN_ELEMENT_END:
				{
					currentSection=L"";
					break;
				}
			}
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

