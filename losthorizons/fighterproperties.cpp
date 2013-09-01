#include "fighterproperties.h"
#include <sstream>

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
