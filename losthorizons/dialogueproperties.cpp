#include "stdafx.h"
#include "dialogueproperties.h"
#include "globals.h"
#include <iostream>
#include <sstream>

using namespace base;

DialogueProperties::DialogueProperties(const std::string &f)
{
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
	DialogueTree *tree = createDialogueTree(file);
	file->drop();
}

DialogueProperties::~DialogueProperties()
{
}

//this is in a seperate function because it needs to be recursive
DialogueTree* DialogueProperties::createDialogueTree(io::IXMLReader *file)
{
	core::stringw currentSection(L"");
	//this will be well commented
	DialogueTree *tree = new DialogueTree;
	if(core::stringw(L"speaker").equals_ignore_case(file->getNodeName()))
	{
		file->getAttributeValue(L"npc");
	}
	while(file->read())
	{
		switch(file->getNodeType())
		{
			case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"text"))
				{
					//grab dialogue
					file->getNodeData();
				}
				break;
			}
			case io::EXN_ELEMENT:
			{
				//grab speaker
				//if we find another speaker make sure we recurse
				if(core::stringw(L"speaker").equals_ignore_case(file->getNodeName()))
				{
					DialogueTree *child = createDialogueTree(file);
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
	return tree;
}
