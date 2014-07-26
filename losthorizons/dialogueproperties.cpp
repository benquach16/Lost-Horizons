#include "stdafx.h"
#include "dialogueproperties.h"
#include "globals.h"
#include <iostream>
#include <sstream>

using namespace base;

DialogueProperties::DialogueProperties(const std::string &f)
{
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());
	core::stringw currentSection(L"");

	while(file->read())
	{
		switch(file->getNodeType())
		{
			case io::EXN_TEXT:
			{
				break;
			}
			case io::EXN_ELEMENT:
			{
				break;
			}
			
		}
	}
}
