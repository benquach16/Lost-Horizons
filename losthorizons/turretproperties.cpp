#include "turretproperties.h"
#include <iostream>
#include <sstream>

TurretProperties::TurretProperties() : turnSpeed(0), reloadSpeed(0), range(0), damage(0)
{
	//default constructor
}

TurretProperties::TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f) : ModelProperties(graphics, f)
{
	//only read the turret values
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
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
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"turretStats").equals_ignore_case(file->getNodeName()))
				{
					turretClass = getTurretClass(file->getAttributeValue(L"class"));
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

TurretProperties::~TurretProperties()
{
}

//protected function
E_TURRET_CLASS TurretProperties::getTurretClass(const std::wstring &str)
{
	if(str == L"light")
	{
		return E_CLASS_LIGHT;
	}
	else if(str == L"medium")
	{
		return E_CLASS_MEDIUM;
	}
	else if(str == L"heavy")
	{
		return E_CLASS_HEAVY;
	}
	else if(str == L"pd")
	{
		return E_CLASS_PD;
	}
	else
	{
		//error!
		std::cout << "Error loading files!" << std::endl;
		std::exit(1);
	}
}

const int& TurretProperties::getMaxTurn() const
{
	return turnSpeed;
}

const float& TurretProperties::getReloadSpeed() const
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
