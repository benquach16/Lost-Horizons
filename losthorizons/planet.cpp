#include "stdafx.h"
#include "planet.h"

//constructor
Planet::Planet(ObjectManager::E_PLANET_LIST planetType, const vector3df& position) : 
	TargetableObject(nextID++, ObjectManager::planetList[planetType], position, vector3df(), E_FACTION_NEUTRAL), cloudMesh(0),
	atmosphere(0)
{
	setTexture(vdriver->getTexture(ObjectManager::planetList[planetType].getDiffuseMap().c_str()));
	//setNormalMap(vdriver->getTexture(ObjectManager::planetList[planetType].getNormalMap().c_str()));
	
	cloudMesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(ObjectManager::planetList[planetType].getFilename().c_str()));
	cloudMesh->setPosition(position);
	cloudMesh->setScale(ObjectManager::planetList[planetType].getScale() + 50);
	cloudMesh->setMaterialTexture(0,vdriver->getTexture(ObjectManager::planetList[planetType].getCloudMap().c_str()));
	cloudMesh->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	
	atmosphere = scenemngr->addBillboardSceneNode(mesh, dimension2df(13000,13000));
	atmosphere->setMaterialTexture(0,vdriver->getTexture("res/textures/atmos.png"));
	atmosphere->setMaterialType(video::EMT_TRANSPARENT_ALPHA_CHANNEL);
	atmosphere->setMaterialFlag(video::EMF_LIGHTING, false);
	//cloudMesh->setMaterialFlag(video::EMF_LIGHTING, false);
	//mesh->setMaterialTexture(1,vdriver->getTexture(ObjectManager::planetList[planetType].getCloudMap().c_str()));
	//enablePlanetShader();
}

Planet::~Planet()
{
	cloudMesh->remove();
	atmosphere->remove();
	//delete atmosphere;
}

void Planet::run()
{
	//atmosphere->run();
}

const E_TARGETABLEOBJECT_TYPE Planet::getTargetableObjectType() const
{
	return E_OBJECT_PLANET;
}

//protected function
void Planet::enablePlanetShader()
{
	PlanetCallback *bp = new PlanetCallback;
	s32 shadermat1 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/planet.hlsl", "VertexShaderFunction", video::EVST_VS_3_0,
		"shaders/planet.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID, (s32)mesh);
	mesh->setMaterialType((video::E_MATERIAL_TYPE)shadermat1);

	bp->drop();
}
