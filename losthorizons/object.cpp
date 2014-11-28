#include "stdafx.h"
#include "object.h"
#include "globals.h"

using namespace base;

std::vector<Object*> Object::allObjects;

//the constructors of this class
//default constructor
Object::Object()
	: mesh(0)
{
}

//constructor with mesh already allocated
Object::Object(scene::IAnimatedMesh *mesh, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: mesh(scenemngr->addAnimatedMeshSceneNode(mesh, 0, -1, position, rotation, scale)), active(true), index(allObjects.size()), iterations(0)
{
	allObjects.push_back(this);
}

//constructor to load mesh from file
Object::Object(const wchar_t *filename, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: filename(filename), mesh(scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename), 0, -1, position, rotation, scale)),
	  active(true), index(allObjects.size()), iterations(0)
{
	allObjects.push_back(this);
	//mesh->setDebugDataVisible(true);
}

//constructor to load mesh and texture from file 
Object::Object(const wchar_t *filename, const wchar_t *tex, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: filename(filename), mesh(scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename), 0, -1, position, rotation, scale)),
	  active(true), index(allObjects.size()), iterations(0)
{
	allObjects.push_back(this);
	//mesh->setDebugDataVisible(true);

	mesh->setMaterialTexture(0, vdriver->getTexture(tex));
}

//copy constructor
Object::Object(const Object *obj)
	: mesh(scenemngr->addAnimatedMeshSceneNode(obj->mesh->getMesh())), active(true), index(allObjects.size()), iterations(0)
{
	allObjects.push_back(this);
	//mesh->setDebugDataVisible(true);
}

//assignment operator
Object& Object::operator=(const Object *obj)
{
	if (obj && this != obj)
	{
		mesh->remove();
		mesh = obj->mesh;
	}
	return *this;
}

Object::~Object()
{
	//swap with back and pop
	mesh->remove();
	allObjects[index] = allObjects.back();
	allObjects[index]->index = index;
	allObjects.pop_back();
}

bool Object::run()
{
	return active;
}

void Object::remove()
{
	active = false;
}

void Object::changeMesh(const wchar_t *filename)
{
	this->filename = filename;
	mesh->remove();
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename));
}

void Object::setTexture(video::ITexture *tex)
{
	mesh->setMaterialTexture(0, tex);
}

void Object::setNormalMap(video::ITexture *normalMap)
{

	BumpMapCallback *bp = new BumpMapCallback;
	s32 shadermat1 = vdriver->getGPUProgrammingServices()->addHighLevelShaderMaterialFromFiles("shaders/bumpmap.hlsl", "VertexShaderFunction", video::EVST_VS_3_0,
		"shaders/bumpmap.hlsl", "PixelShaderFunction", video::EPST_PS_3_0, bp, video::EMT_SOLID);

	mesh->setMaterialType((video::E_MATERIAL_TYPE)shadermat1);
	mesh->setMaterialTexture(1, normalMap);
	bp->drop();
}

const vector3df& Object::getPosition() const
{
	return mesh->getPosition();
}

const vector3df& Object::getRotation() const
{
	return  mesh->getRotation();
}

const vector3df& Object::getScale() const
{
	return  mesh->getScale();
}

const core::aabbox3df Object::getBoundingBox() const
{
	return mesh->getTransformedBoundingBox();
}

const bool Object::getVisible() const
{
	return visible;
}

const bool Object::getActive() const
{
	return active;
}

const int Object::getIterations() const
{
	return iterations;
}

void Object::setPosition(const vector3df &position)
{
	mesh->setPosition(position);
}

void Object::setRotation(const vector3df &rotation)
{
	mesh->setRotation(rotation);
}

void Object::setScale(const vector3df &scale)
{
	mesh->setScale(scale);
}

void Object::setVisible(const bool visible)
{
	this->visible = visible;
	mesh->setVisible(visible);
}

void Object::incrementIterations()
{
	iterations++;
}
