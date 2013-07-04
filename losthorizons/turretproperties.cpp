#include "turretproperties.h"

TurretProperties::TurretProperties() : maxTurn(0), reloadSpeed(0)
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

		}
	}

	file->drop();
}

TurretProperties::~TurretProperties()
{
}
