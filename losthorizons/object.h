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
	Object();
	//copy constructor
	Object(const Object *obj);
	virtual ~Object();
	virtual void run();

	const vector3df getPosition() const;
	const vector3df getRotation() const;
	const vector3df getScale() const;

private:
	vector3df position;
	vector3df rotation;
	vector3df scale;
};

#endif
