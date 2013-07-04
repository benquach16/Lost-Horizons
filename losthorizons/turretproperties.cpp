#include "turretproperties.h"

TurretProperties::TurretProperties() : turnSpeed(0), reloadSpeed(0), range(0), damage(0)
{
	//default constructor
}

TurretProperties::TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f) 
{
	//only read the turret values
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	while(file->read())
	{
		//read turret properties
		if(core::stringw(L"turretStats").equals_ignore_case(file->getNodeName()))
		{
			turnSpeed = file->getAttributeValueAsInt(L"turnSpeed");
			damage = file->getAttributeValueAsInt(L"damage");
			reloadSpeed = file->getAttributeValueAsFloat(L"reloadSpeed");
			range = file->getAttributeValueAsInt(L"range");
		}
	}

	file->drop();
}

TurretProperties::~TurretProperties()
{
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
