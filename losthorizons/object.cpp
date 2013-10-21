#include "object.h"
#include "globals.h"

using namespace base;

std::list<Object*> Object::allObjects;

//the constructors of this class
//default constructor
Object::Object() : mesh(0), position(vector3df(0,0,0)), rotation(vector3df(0,0,0)), scale(vector3df(0,0,0))
{
}

//constructor with mesh already allocated
Object::Object(scene::IAnimatedMesh *m, const vector3df &position, const vector3df &rotation, const vector3df &scale) :
	position(position), rotation(rotation), scale(scale)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(m);
	mesh->setPosition(position);
	mesh->setRotation(rotation);
	mesh->setScale(scale);
	allObjects.push_front(this);
	it = allObjects.begin();
}

//constructor to load mesh from file
Object::Object(const wchar_t *filename, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: position(position), rotation(rotation), scale(scale), filename(filename)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename));
	mesh->setPosition(position);
	mesh->setRotation(rotation);
	mesh->setScale(scale);
	allObjects.push_front(this);
	it = allObjects.begin();
	//mesh->setDebugDataVisible(true);
}

//constructor to load mesh and texture from file 
Object::Object(const wchar_t *filename, const wchar_t *tfilename, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: position(position), rotation(rotation), scale(scale), filename(filename)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename));
	mesh->setMaterialTexture(0, vdriver->getTexture(tfilename));
	mesh->setPosition(position);
	mesh->setRotation(rotation);
	mesh->setScale(scale);
	allObjects.push_front(this);
	it = allObjects.begin();
	//mesh->setDebugDataVisible(true);
}

//copy constructor
Object::Object(const Object *obj) : position(obj->getPosition()), rotation(obj->getRotation()), scale(obj->getScale())
{
	mesh = scenemngr->addAnimatedMeshSceneNode(obj->mesh->getMesh());
	mesh->setPosition(position);
	mesh->setRotation(rotation);
	mesh->setScale(scale);
}

//assignment operator
Object& Object::operator=(const Object *obj)
{
	if(obj && this != obj)
	{
		position = obj->position;
		rotation = obj->rotation;
		scale = obj->scale;
		mesh->remove();
		mesh = obj->mesh;
	}
	return *this;
}

Object::~Object()
{
	allObjects.erase(it);
	mesh->remove();
}

void Object::run(f32 frameDeltaTime)
{
}

void Object::reloadMesh()
{
	mesh = scenemngr->addAnimatedMeshSceneNode(scenemngr->getMesh(filename.c_str()));
}

void Object::changeMesh(const wchar_t *filename)
{
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
	return position;
}

const vector3df& Object::getRotation() const
{
	return rotation;
}

const vector3df& Object::getScale() const
{
	return scale;
}

const core::aabbox3df Object::getBoundingBox() const
{
	return mesh->getTransformedBoundingBox();
}

const bool Object::getVisible() const
{
	return visible;
}

void Object::setPosition(const vector3df &newPosition)
{
	position = newPosition;
	mesh->setPosition(position);
}

void Object::setRotation(const vector3df &newRotation)
{
	rotation = newRotation;
	mesh->setRotation(rotation);
}

void Object::setScale(const vector3df &newScale)
{
	scale = newScale;
	mesh->setScale(scale);
}

void Object::setVisible(bool newVisibility)
{
	visible = newVisibility;
	mesh->setVisible(newVisibility);
}

