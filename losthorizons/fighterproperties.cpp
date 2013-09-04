#include "fighterproperties.h"
#include <sstream>

FighterProperties::FighterProperties() : maxHull(0), maxTurn(0), maxVelocity(0), maxFuel(0), ModelProperties()
{
}

FighterProperties::FighterProperties(irr::IrrlichtDevice *graphics, const std::string &f) : ModelProperties(graphics, f)
{
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
					std::wstringstream iss(file->getNodeData());
					iss >> maxHull;
				}
				if(currentSection.equals_ignore_case(L"maxTurn"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxTurn;
				}
				if(currentSection.equals_ignore_case(L"maxVelocity"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxVelocity;
				}
				if(currentSection.equals_ignore_case(L"maxFuel"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxFuel;
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"maxHull").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxHull";
				}
				if(core::stringw(L"maxTurn").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxTurn";
				}
				if(core::stringw(L"maxVelocity").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxVelocity";
				}
				if(core::stringw(L"maxFuel").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxFuel";
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

FighterProperties::~FighterProperties()
{
}

const int FighterProperties::getMaxHull() const
{
	return maxHull;
}

const int FighterProperties::getMaxTurn() const
{
	return maxTurn;
}

const int FighterProperties::getMaxVelocity() const
{
	return maxVelocity;
}

const unsigned FighterProperties::getMaxFuel() const
{
	return maxFuel;
}