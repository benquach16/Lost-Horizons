#include "modelproperties.h"
#include <sstream>

ModelProperties::ModelProperties() : filename(L""), diffuseMap(L""), normalMap(L""), scale(core::vector3df(1.f,1.f,1.f)), ItemProperties()
{
	//default constructor
}

ModelProperties::ModelProperties(irr::IrrlichtDevice *graphics, const std::string &f) : ItemProperties(graphics, f), scale(core::vector3df(1.f,1.f,1.f))
{
	//only read model values
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	//since we have dem nests
	core::stringw currentSection(L"");
	core::stringw currentTree(L"");
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
				if(core::stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
				{
					currentTree=L"modelStats";
				}
				if(core::stringw(L"filename").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"filename";
				}
				if(core::stringw(L"modelStats").equals_ignore_case(currentTree) && core::stringw(L"diffuseMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"diffuseMap";
				}
				if(core::stringw(L"modelStats").equals_ignore_case(currentTree) && core::stringw(L"normalMap").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"normalMap";
				}
				if(core::stringw(L"modelStats").equals_ignore_case(currentTree) && core::stringw(L"scaleX").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleX";
				}
				if(core::stringw(L"modelStats").equals_ignore_case(currentTree) && core::stringw(L"scaleY").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleY";
				}
				if(core::stringw(L"modelStats").equals_ignore_case(currentTree) && core::stringw(L"scaleZ").equals_ignore_case(file->getNodeName()))
				{
					currentSection=L"scaleZ";
				}
				break;
			}
		case io::EXN_ELEMENT_END:
			{
				if(core::stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
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

const core::vector3df& ModelProperties::getScale() const
{
	return scale;
}
