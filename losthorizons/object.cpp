//#include "stdafx.h"
#include "object.h"

//the constructors of this class
Object::Object() : mesh(0), position(vector3df(0,0,0)), rotation(vector3df(0,0,0)), scale(vector3df(0,0,0))
{

}

Object::Object(irr::IrrlichtDevice *graphics, IAnimatedMesh *mesh, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: mesh(graphics->getSceneManager()->addAnimatedMeshSceneNode(mesh)), position(position), rotation(rotation), scale(scale)
{

}

Object::Object(irr::IrrlichtDevice *graphics, const wchar_t *filename, const vector3df &position, const vector3df &rotation,
			   const vector3df &scale)
	: position(position), rotation(rotation), scale(scale)
{
	graphics->getSceneManager()->addAnimatedMeshSceneNode(graphics->getSceneManager()->getMesh(filename));
}

//copy constructor
Object::Object(const Object *obj)
{
	position = obj->position;
	rotation = obj->rotation;
	scale = obj->scale;
	mesh = obj->mesh;
}

//assignment operator
Object& Object::operator=(const Object *obj)
{
	position = obj->position;
	rotation = obj->rotation;
	scale = obj->scale;
	mesh->drop();
	mesh = obj->mesh;
	return *this;
}

Object::~Object()
{
	mesh->drop();
}

void Object::run()
{

}

const vector3df Object::getPosition() const
{
	return position;
}

const vector3df Object::getRotation() const
{
	return rotation;
}

const vector3df Object::getScale() const
{
	return scale;
}
