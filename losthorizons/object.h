#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "irrlicht.h"

using namespace irr;
using namespace core;
using namespace scene;

//all objects are associated with a faction
enum E_GAME_FACTIONS
{
	E_FACTION_TERRAN,
	E_FACTION_PROVIAN,
	E_FACTION_TRADER,
	E_FACTION_NEUTRAL
};

//This is the base class of all renderable (3d really) objects in the game
class Object
{
public:

	//default constructor
	Object();
	//parametrized constructors
	//instantiate with position, rotation, etc
	Object(IAnimatedMesh *mesh, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));
	//instantiate with filename
	Object(irr::IrrlichtDevice *graphics, const wchar_t *filename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));
	//copy constructor
	Object(const Object *obj);
	//overloaded assignment operator
	Object& operator=(const Object *obj);

	//desctructor
	virtual ~Object();
	virtual void run();

	//returns an rvalue
	const vector3df getPosition() const;
	const vector3df getRotation() const;
	const vector3df getScale() const;
	//mutators
	void setPosition(const vector3df &newPosition);
	void setRotation(const vector3df &newRotation);
	void setScale(const vector3df &newScale);

protected:

	//basic info about object
	vector3df position;
	vector3df rotation;
	vector3df scale;

	//3d infomation
	IAnimatedMesh *mesh;

};

#endif
