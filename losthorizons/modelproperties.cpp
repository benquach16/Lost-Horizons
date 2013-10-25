#include "stdafx.h"
#include "modelproperties.h"
#include "globals.h"
#include <sstream>

using namespace base;

ModelProperties::ModelProperties(const std::string &f) : ItemProperties(f), scale(vector3df(1.f,1.f,1.f))
{
	//only read model values
	io::IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	//since we have dem nests
	stringw currentSection(L"");
	stringw currentTree(L"");
	while(file->read())
	{
		switch(file->getNodeType())
		{
		case io::EXN_TEXT:
			{
				if(currentSection.equals_ignore_case(L"filename"))
				{
					filename = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"diffuseMap"))
				{
					diffuseMap = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"normalMap"))
				{
					normalMap = file->getNodeData();
				}
				if(currentSection.equals_ignore_case(L"scaleX"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> scale.X;					
				}
				if(currentSection.equals_ignore_case(L"scaleY"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> scale.Y;					
				}
				if(currentSection.equals_ignore_case(L"scaleZ"))
				{
					std::wstringstream iss(file->getNodeData());
					iss >> scale.Z;					
				}
				break;
			}
		case io::EXN_ELEMENT:
			{
				if(stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree=L"modelStats";
				}
				if(stringw(L"filename").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"filename";
				}
				if(stringw(L"modelStats").equals_ignore_case(currentTree) && stringw(L"diffuseMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"diffuseMap";
				}
				if(stringw(L"modelStats").equals_ignore_case(currentTree) && stringw(L"normalMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"normalMap";
				}
				if(stringw(L"modelStats").equals_ignore_case(currentTree) && stringw(L"scaleX").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleX";
				}
				if(stringw(L"modelStats").equals_ignore_case(currentTree) && stringw(L"scaleY").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleY";
				}
				if(stringw(L"modelStats").equals_ignore_case(currentTree) && stringw(L"scaleZ").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleZ";
				}
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				if(stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree=L"";
				}
				currentSection=L"";
				break;
			}
		}
	}

	file->drop();
}

ModelProperties::~ModelProperties()
{
}

const std::wstring& ModelProperties::getFilename() const
{
	return filename;
}
const std::wstring& ModelProperties::getDiffuseMap() const
{
	return diffuseMap;
}
const std::wstring& ModelProperties::getNormalMap() const
{
	return normalMap;
}

const vector3df& ModelProperties::getScale() const
{
	return scale;
}
