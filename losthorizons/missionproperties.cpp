#include "missionproperties.h"
#include <iostream>

MissionProperties::MissionProperties(irr::IrrlichtDevice *graphics, const std::string &f)
{
	//read from xml file
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	//keep track of which tree we're in
	core::stringw currentSection(L"");
	core::stringw currentTree(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"name") && currentTree.equals_ignore_case(L""))
				{
					name = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"description") && currentTree.equals_ignore_case(L""))
				{
					description = file->getNodeData();
				}

				break;
			}
		case io::EXN_ELEMENT:
			{
				if(core::stringw(L"name").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L""))
				{
					//read mission name
					currentSection=L"name";
				}
				if(core::stringw(L"description").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L""))
				{
					//read mission description
					currentSection=L"description";
				}				
				if(core::stringw(L"createShip").equals_ignore_case(file->getNodeName()))
				{
					file->getAttributeValue(L"type");
					file->getAttributeValue(L"faction");
					file->getAttributeValueAsFloat(L"posX");
					file->getAttributeValueAsFloat(L"posY");
					file->getAttributeValueAsFloat(L"posZ");

				}
				if(core::stringw(L"objectives").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L""))
				{
					//enter a new tree!!!
					currentTree = L"objectives";
					numOfObjectives = file->getAttributeValueAsInt(L"num");
				}				
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				if(currentTree.equals_ignore_case(file->getNodeName()))
				{
					//cut tree
					currentTree = L"";
				}	
				break;
			}
		}
	}
	file->drop();
}

MissionProperties::~MissionProperties()
{
}

//protected function
E_OBJECTIVE_TYPE MissionProperties::getObjectiveType(const wchar_t *text)
{
	if(text == L"sweep")
		return OBJECTIVE_SWEEP;
	else
	{
		std::cout << "Failed to read from mission file!" << std::endl;
		exit(1);
	}
}
