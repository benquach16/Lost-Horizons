#include "stdafx.h"
#include "object.h"

//the constructors of this class
Object::Object() : mesh(0), position(vector3df(0,0,0)), rotation(vector3df(0,0,0)), scale(vector3df(0,0,0))
{

}

Object::Object(irr::IrrlichtDevice *graphics, IAnimatedMesh *mesh, const vector3df &position, const vector3df &rotation, const vector3df &scale)
	: mesh(graphics->getSceneManager()->addAnimatedMeshSceneNode(mesh)), position(position), rotation(rotation), scale(scale)
{
	this->mesh->setPosition(position);
	this->mesh->setRotation(rotation);
	this->mesh->setScale(scale);
}

Object::Object(irr::IrrlichtDevice *graphics, const wchar_t *filename, const vector3df &position, const vector3df &rotation,
			   const vector3df &scale)
	: position(position), rotation(rotation), scale(scale)
{
	mesh = scenemngr->addAnimatedMeshSceneNode(graphics->getSceneManager()->getMesh(filename));
	mesh->setPosition(position);
	mesh->setRotation(rotation);
	mesh->setScale(scale);
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

//accessors
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
