#include "planetproperties.h"

PlanetProperties::PlanetProperties()
{
}

PlanetProperties::PlanetProperties(irr::IrrlichtDevice *graphics, const std::string &f)
{
	//read in planet properties
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
}

PlanetProperties::~PlanetProperties()
{
}
