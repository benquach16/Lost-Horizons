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
				if(core::stringw(L"create").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L""))
				{
					//create tree!
					currentTree = L"create";
				}
				if(core::stringw(L"ship").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L"create"))
				{
					//create ship
					//read into enums
					int type = file->getAttributeValueAsInt(L"type");
					int faction = file->getAttributeValueAsInt(L"faction");
					float x = file->getAttributeValueAsFloat(L"posX");
					float y = file->getAttributeValueAsFloat(L"posY");
					float z = file->getAttributeValueAsFloat(L"posZ");
					Ship *s = new Ship((E_GAME_FACTION)faction, (ObjectManager::E_SHIP_LIST)type,
						vector3df(x,y,z), vector3df());
				}
				if(core::stringw(L"objectives").equals_ignore_case(file->getNodeName()) && currentTree.equals_ignore_case(L""))
				{
					//enter a new tree!!!
					currentTree = L"objectives";
					numOfObjectives = file->getAttributeValueAsInt(L"num");
					for(unsigned i = 0; i < numOfObjectives; i++)
					{
						char temp[2] = {0};
						temp[0] = (i+'A');
						if(core::stringw(temp).equals_ignore_case(file->getNodeName()))
						{
							//create objectives
							E_OBJECTIVE_TYPE type = getObjectiveType(file->getAttributeValue(L"type"));
							float x = file->getAttributeValueAsFloat(L"posX");
							float y = file->getAttributeValueAsFloat(L"posY");
							float z = file->getAttributeValueAsFloat(L"posZ");
							int radius = file->getAttributeValueAsInt(L"radius");
							Objective obj(type, vector3df(x,y,z), radius);
							objectives.push_back(obj);
						}
					}
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

const std::wstring& MissionProperties::getName() const
{
	return name;
}

const std::wstring& MissionProperties::getDesc() const
{
	return description;
}

const std::vector<Objective>& MissionProperties::getObjs() const
{
	return objectives;
}

//protected function
E_OBJECTIVE_TYPE MissionProperties::getObjectiveType(const wchar_t *text)
{
	if(text == L"sweep")
		return OBJECTIVE_SWEEP;
	else if(text == L"courier")
		return OBJECTIVE_COURIER;
	else if(text == L"navigate")
		return OBJECTIVE_NAVIGATE;
	else if(text == L"retrieval")
		return OBJECTIVE_RETRIEVAL;
	else if(text == L"defend")
		return OBJECTIVE_DEFEND;
	else
	{
		std::cout << "Failed to read from mission file!" << std::endl;
		exit(1);
	}
}


