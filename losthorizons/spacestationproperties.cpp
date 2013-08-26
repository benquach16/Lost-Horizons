#include "spacestationproperties.h"
#include <sstream>

SpaceStationProperties::SpaceStationProperties(irr::IrrlichtDevice *graphics, const std::string &f) : ModelProperties(graphics, f)
{
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	//read from xml
	core::stringw currentSection(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"spawnShips"))
				{
					spawnShips = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"spawnFighters"))
				{
					spawnFighters = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"serviceFitting"))
				{
					serviceFitting = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"serviceJobBoard"))
				{
					serviceJobBoard = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"serviceShipYard"))
				{
					serviceShipYard = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"buyMarkupFactor"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> buyMarkupFactor;
				}
				if(currentSection.equals_ignore_case(L"sellMarkdownFactor"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> sellMarkdownFactor;
				}
				if(currentSection.equals_ignore_case(L"isHQ"))
				{
					isHQ = getTrueOrFalse(file->getNodeData());
				}
				if(currentSection.equals_ignore_case(L"shipSpawnTimer"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> shipSpawnTimer;
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"spawnShips").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"spawnShips";
				}
				if(core::stringw(L"spawnFighters").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"spawnFighters";
				}
				if(core::stringw(L"serviceFitting").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"serviceFitting";
				}
				if(core::stringw(L"serviceJobBoard").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"serviceJobBoard";
				}
				if(core::stringw(L"serviceShipYard").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"serviceShipYard";
				}
				if(core::stringw(L"buyMarkupFactor").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"buyMarkupFactor";
				}
				if(core::stringw(L"sellMarkdownFactor").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"sellMarkdownFactor";
				}
				if(core::stringw(L"isHQ").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"isHQ";
				}
				if(core::stringw(L"shipSpawnTimer").equals_ignore_case(file->getNodeName()))
				{
					currentSection = L"shipSpawnTimer";
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
	file->drop();
}

SpaceStationProperties::~SpaceStationProperties()
{
}

//protected function
bool SpaceStationProperties::getTrueOrFalse(const wchar_t *text)
{
	if(text == L"false")
	{
		return false;
	}
	else
		return true;
}
