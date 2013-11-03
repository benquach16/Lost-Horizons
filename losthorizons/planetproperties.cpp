#include "stdafx.h"
#include "planetproperties.h"
#include "globals.h"
#include <sstream>

using namespace base;

PlanetProperties::PlanetProperties(const std::string &f) : ModelProperties(f)
{
	//read in planet properties
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
	core::stringw currentSection(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"cloudMap"))
				{
					cloudMap = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"maxPopulation"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxPopulation;
				}
				if(currentSection.equals_ignore_case(L"maxDevelopmentIndex"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxDevelopmentIndex;
				}
				if(currentSection.equals_ignore_case(L"maxTechLevel"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> maxTechLevel;
				}
				break;
			}

		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"cloudMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"cloudMap";
				}
				if(core::stringw(L"maxPopulation").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxPopulation";
				}
				if(core::stringw(L"maxTechLevel").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxTechLevel";
				}
				if(core::stringw(L"maxTechLevel").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"maxTechLevel";
				}
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				currentSection = L"";
				break;
			}
		}
	}
}

PlanetProperties::~PlanetProperties()
{
}

const wchar_t *PlanetProperties::getCloudMap() const
{
	return cloudMap.c_str();
}
