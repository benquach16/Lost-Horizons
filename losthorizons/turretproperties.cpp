#include "stdafx.h"
#include "turretproperties.h"
#include "globals.h"
#include <iostream>
#include <sstream>

using namespace base;

TurretProperties::TurretProperties(const std::string &f) : ModelProperties(f)
{
	//only read the turret values
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
	core::stringw currentTree(L"");
	core::stringw currentSection(L"");
	while(file->read())
	{
		//read turret properties
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"turnSpeed"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> turnSpeed;
				}
				if(currentSection.equals_ignore_case(L"damage"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> damage;
				}
				if(currentSection.equals_ignore_case(L"range"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> range;
				}
				if(currentSection.equals_ignore_case(L"reloadSpeed"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> reloadSpeed;
				}
				if(currentSection.equals_ignore_case(L"projectileSpeed"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> projectileSpeed;
				}
				if(currentSection.equals_ignore_case(L"energyUse"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> energyUse;
				}
				if(currentSection.equals_ignore_case(L"fireSound"))
				{
					std::wstring tmp = file->getNodeData();
					soundFilename = std::string(tmp.begin(), tmp.end());
				}
				if(currentTree.equals_ignore_case(L"projectileStats") && currentSection.equals_ignore_case(L"scaleX"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> projectileScale.X;
				}
				if(currentTree.equals_ignore_case(L"projectileStats") && currentSection.equals_ignore_case(L"scaleY"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> projectileScale.Y;
				}
				if(currentTree.equals_ignore_case(L"projectileStats") && currentSection.equals_ignore_case(L"scaleZ"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> projectileScale.Z;
				}
				if(currentTree.equals_ignore_case(L"projectileStats") && currentSection.equals_ignore_case(L"diffuseMap"))
				{
					projectileTexture = file->getNodeData();
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"turretStats").equals_ignore_case(file->getNodeName()))
				{
					turretClass = getTurretClass(file->getAttributeValue(L"class"));
					turretType = getTurretType(file->getAttributeValue(L"type"));
					currentTree=L"turretStats";

				}
				if(core::stringw(L"fireSound").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"fireSound";
				}
				if(core::stringw(L"projectileStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree=L"projectileStats";
				}
				if(core::stringw(L"turnSpeed").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"turnSpeed";
				}
				if(core::stringw(L"damage").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"damage";
				}
				if(core::stringw(L"range").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"range";
				}
				if(core::stringw(L"reloadSpeed").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"reloadSpeed";
				}
				if(core::stringw(L"projectileSpeed").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"projectileSpeed";
				}
				if(core::stringw(L"energyUse").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"energyUse";
				}
				if(core::stringw(L"scaleX").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleX";
				}
				if(core::stringw(L"scaleY").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleY";
				}
				if(core::stringw(L"scaleZ").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleZ";
				}
				if(core::stringw(L"diffuseMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"diffuseMap";
				}
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				if(core::stringw(L"turretStats").equals_ignore_case(currentTree) && core::stringw(L"turretStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree = L"";
				}
				if(core::stringw(L"projectileStats").equals_ignore_case(currentTree) && core::stringw(L"projectileStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree = L"";
				}
				currentSection=L"";
				break;
			}
		}
	}

	file->drop();
}

TurretProperties::~TurretProperties()
{
}

//accessors
const int& TurretProperties::getMaxTurn() const
{
	return turnSpeed;
}

const f32& TurretProperties::getReloadSpeed() const
{
	return reloadSpeed;
}

const int& TurretProperties::getDamage() const
{
	return damage;
}

const int& TurretProperties::getRange() const
{
	return range;
}

const int& TurretProperties::getProjectileSpeed() const
{
	return projectileSpeed;
}

const int TurretProperties::getEnergyUse() const
{
	return energyUse;
}

const wchar_t *TurretProperties::getProjectileTex() const
{
	return projectileTexture.c_str();
}

const char *TurretProperties::getSoundFilename() const
{
	return soundFilename.c_str();
}

const core::vector3df& TurretProperties::getProjectileScale() const
{
	return projectileScale;
}

const E_TURRET_CLASS TurretProperties::getTurretClass() const
{
	return turretClass;
}

const E_TURRET_TYPE TurretProperties::getWeaponType() const
{
	return turretType;
}

//protected function
E_TURRET_CLASS TurretProperties::getTurretClass(const std::wstring &str)
{
	if(str == L"heavy")
	{
		return TURRET_HEAVY;
	}
	else if(str == L"medium")
	{
		return TURRET_MEDIUM;
	}
	else if(str == L"light")
	{
		return TURRET_LIGHT;
	}
	else if(str == L"pd")
	{
		return TURRET_PD;
	}
	else
	{
		//error!
		std::cout << "Error loading turret information!" << std::endl;
		std::exit(1);
	}
}

//protected function
E_TURRET_TYPE TurretProperties::getTurretType(const std::wstring &str)
{
	if(str == L"direct")
	{
		return TURRET_TYPE_DIRECT;
	}
	else if(str == L"missile")
	{
		return TURRET_TYPE_MISSILE;
	}
	else if(str == L"laser")
	{
		return TURRET_TYPE_LASER;
	}
	else
	{
		//error!
		std::cout << "Error loading turret information!" << std::endl;
		std::exit(1);
	}
}
