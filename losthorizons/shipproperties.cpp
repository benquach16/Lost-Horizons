//#include "stdafx.h"
#include "shipproperties.h"
#include <iostream>
#include <sstream>

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
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"maxHull"))
				{
					//read hull
					std::wstringstream iss(file->getNodeData());
					iss >> maxHull;
				}
				if(currentSection.equals_ignore_case(L"maxArmor"))
				{
					//read hull
					std::wstringstream iss(file->getNodeData());
					iss >> maxArmor;
				}
				if(currentSection.equals_ignore_case(L"maxShield"))
				{
					//read hull
					std::wstringstream iss(file->getNodeData());
					iss >> maxShield;
				}
				if(currentSection.equals_ignore_case(L"maxVelocity"))
				{
					//read velocity
					std::wstringstream iss(file->getNodeData());
					iss >> maxVelocity;
				}
				if(currentSection.equals_ignore_case(L"maxTurn"))
				{
					//read turn
					std::wstringstream iss(file->getNodeData());
					iss >> maxTurn;
				}
				if(currentSection.equals_ignore_case(L"maxEnergy"))
				{
					//read ernergy
					std::wstringstream iss(file->getNodeData());
					iss >> maxEnergy;
				}
				if(currentSection.equals_ignore_case(L"maxCrew"))
				{
					//read crew
					std::wstringstream iss(file->getNodeData());
					iss >> maxCrew;
				}
				if(currentSection.equals_ignore_case(L"maxFighters"))
				{
					//read fighters
					std::wstringstream iss(file->getNodeData());
					iss >> maxFighters;
				}
				if(currentSection.equals_ignore_case(L"maxCargo"))
				{
					//read cargo size
					std::wstringstream iss(file->getNodeData());
					iss >> maxCargo;
				}
				if(currentSection.equals_ignore_case(L"numEngines"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> numEngines;
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"maxHull").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxHull";
				}
				if(core::stringw(L"maxArmor").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxArmor";
				}
				if(core::stringw(L"maxShield").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxShield";
				}
				if(core::stringw(L"maxVelocity").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxVelocity";
				}
				if(core::stringw(L"maxTurn").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxTurn";
				}
				if(core::stringw(L"maxEnergy").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxEnergy";
				}
				if(core::stringw(L"maxCrew").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxCrew";
				}
				if(core::stringw(L"maxFighters").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxFighters";
				}
				if(core::stringw(L"maxCargo").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"maxCargo";
				}
				if(core::stringw(L"numEngines").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"numEngines";
				}
				if(core::stringw(L"heavyTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"heavyTurret";
					maxHeavyTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"heavyTurret"))
				{
					//read turrets
					//prepare for da loopz
					for(int i = 0; i < maxHeavyTurrets; i++)
					{
						char temp[2] = {0};
						temp[0] = (i+'A');
						if(core::stringw(temp).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsInt(L"arc");
							heavyTurrets.push_back(tmp);
						}
					}
				}
				if(core::stringw(L"mediumTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"mediumTurret";
					maxMediumTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"mediumTurret"))
				{
					//read turrets
					//prepare for da loopz
					for(int i = 0; i < maxMediumTurrets; i++)
					{
						char temp[2] = {0};
						temp[0] = (i+'A');
						if(core::stringw(temp).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsInt(L"arc");
							mediumTurrets.push_back(tmp);
						}
					}
				}
				if(core::stringw(L"lightTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"lightTurret";
					maxLightTurrets = file->getAttributeValueAsInt(L"num");
				}
				else if(currentSection.equals_ignore_case(L"lightTurret"))
				{
					//read turrets
					//prepare for da loopz
					for(int i = 0; i < maxLightTurrets; i++)
					{
						char temp[2] = {0};
						temp[0] = (i+'A');
						if(core::stringw(temp).equals_ignore_case(file->getNodeName()))
						{
							//load turret information
							turretInformation tmp;
							tmp.rotation.X = file->getAttributeValueAsFloat(L"rotationX");
							tmp.rotation.Y = file->getAttributeValueAsFloat(L"rotationY");
							tmp.rotation.Z = file->getAttributeValueAsFloat(L"rotationZ");
							tmp.arc = file->getAttributeValueAsInt(L"arc");
							lightTurrets.push_back(tmp);
						}
					}
				}
				if(core::stringw(L"pdTurret").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"pdTurret";
					maxPDTurrets = file->getAttributeValueAsInt(L"num");
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


ShipProperties::~ShipProperties()
{
}

//accessors
const int& ShipProperties::getMaxHull() const
{
	return maxHull;
}

const int& ShipProperties::getMaxArmor() const
{
	return maxArmor;
}

const int& ShipProperties::getMaxShield() const
{
	return maxShield;
}

const int& ShipProperties::getMaxTurn() const
{
	return maxTurn;
}

const f32& ShipProperties::getMaxVel() const
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

const int& ShipProperties::getMaxCargo() const
{
	return maxCargo;
}
const int& ShipProperties::getNumEngines() const
{
	return numEngines;
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
