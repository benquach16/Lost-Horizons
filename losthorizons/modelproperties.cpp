#include "modelproperties.h"

ModelProperties::ModelProperties() : filename(L""), diffuseMap(L""), normalMap(L""), scale(core::vector3df(1.f,1.f,1.f)), ItemProperties()
{
	//default constructor
}

ModelProperties::ModelProperties(irr::IrrlichtDevice *graphics, const std::string &f) : ItemProperties(graphics, f)
{
	//only read model values
	IXMLReader *file = graphics->getFileSystem()->createXMLReader(f.c_str());

	while(file->read())
	{
		if(core::stringw(L"modelStats").equals_ignore_case(file->getNodeName()))
		{
			filename = file->getAttributeValue(L"filename");
			diffuseMap = file->getAttributeValue(L"diffuseMap");
			normalMap = file->getAttributeValue(L"normalMap");

			scale.X = file->getAttributeValueAsFloat(L"scaleX");
			scale.Y = file->getAttributeValueAsFloat(L"scaleY");
			scale.Z = file->getAttributeValueAsFloat(L"scaleZ");
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
