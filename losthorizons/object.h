#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;

//This is the base class of all renderable (3d really) objects in the game

class Object
{
public:

	//default constructor
	Object();
	//parametrized constructors
	//instantiate with position, rotation, etc
	Object(IAnimatedMesh *mesh, vector3df position = vector3df(0,0,0),
		vector3df rotation = vector3df(0,0,0), vector3df scale = vector3df(1,1,1));
	//copy constructor
	Object(const Object *obj);
	virtual ~Object();
	virtual void run();

	const vector3df getPosition() const;
	const vector3df getRotation() const;
	const vector3df getScale() const;

private:

	//basic info about object
	vector3df position;
	vector3df rotation;
	vector3df scale;

	//3d infomation
	IAnimatedMesh *mesh;

};

#endif
