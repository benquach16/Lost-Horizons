#include "stdafx.h"
#include "planet.h"

//constructor
Planet::Planet(ObjectManager::E_PLANET_LIST planetType, const vector3df& position) : 
	TargetableObject(nextID++, ObjectManager::planetList[planetType], position, vector3df())
{
	setTexture(vdriver->getTexture(ObjectManager::planetList[planetType].getDiffuseMap().c_str()));
	setNormalMap(vdriver->getTexture(ObjectManager::planetList[planetType].getNormalMap().c_str()));
	//enablePlanetShader();
}

Planet::~Planet()
{
}

void Planet::run()
{
}

void Planet::enablePlanetShader()
{
	PlanetCallback *bp = new PlanetCallback;
	s32 shadermat1 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/planet.hlsl", "VertexShaderFunction", video::EVST_VS_3_0,
		"shaders/planet.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID, (s32)mesh);
	mesh->setMaterialType((video::E_MATERIAL_TYPE)shadermat1);

	bp->drop();
}
