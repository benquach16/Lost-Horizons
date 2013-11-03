#ifndef _MODELPROPERTIES_H_
#define _MODELPROPERTIES_H_

#include "itemproperties.h"

//if we need to read model information from xmls
class ModelProperties : public ItemProperties
{
public:
	ModelProperties();
	ModelProperties(const std::string &f);
	~ModelProperties();

	const wchar_t *getFilename() const;
	const wchar_t *getDiffuseMap() const;
	const wchar_t *getNormalMap() const;

	const core::vector3df& getScale() const;
	
protected:
	//model information
	std::wstring filename;
	std::wstring diffuseMap;
	std::wstring normalMap;

	core::vector3df scale;
};

#endif
