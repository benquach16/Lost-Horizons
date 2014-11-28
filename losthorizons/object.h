#ifndef _OBJECT_H_
#define _OBJECT_H_

#include "stdafx.h"
#include "callback.h"
#include <string>
#include <vector>

using namespace irr;
using namespace core;

//all objects are associated with a faction
enum E_GAME_FACTION
{
	FACTION_TERRAN,
	FACTION_PROVIAN,
	FACTION_PIRATE,
	FACTION_NEUTRAL
};

//we need to move a shitton of stuff to get save loading to work with this system
enum E_OBJECT_COMPONENTS
{
	COMPONENT_DAMAGEABLE = 0x0001, //2^n
	COMPONENT_MOVEABLE = 0x0002,
	COMPONENT_FACTION = 0x0004,
	COMPONENT_CANTARGET = 0x0008,
	COMPONENT_TARGETABLE = 0x0010,
};

//This is the base class of all renderable (3d really) objects in the game
class Object
{
public:
	static std::vector<Object*> allObjects;

	//default constructor
	Object();

	//parametrized constructors
	//instantiate with position, rotation, etc
	Object(scene::IAnimatedMesh *mesh, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));

	//instantiate with filename
	//const wchar_t *filename = filepath of the mesh
	Object(const wchar_t *filename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));

	//parameterized constructor with texture overloading
	Object(const wchar_t *filename, const wchar_t *tex, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));

	//copy constructor
	Object(const Object *obj);
	//overloaded assignment operator
	Object& operator=(const Object *obj);

	//desctructor
	virtual ~Object();

	//returns whether the object wants to be deleted or not
	virtual bool run();

	void remove();

	//meant for use by planets and ships to show ingame info
	//moved to targetable object class
	//virtual void information() {}
	//change the mesh to a new one
	void changeMesh(const wchar_t *filename);
	//set the diffuse map of the mesh
	void setTexture(video::ITexture *tex);
	//set the normal map of the mesh
	//automatically enable shaders if this happens
	void setNormalMap(video::ITexture *normalMap);

	//accessors
	const vector3df& getPosition() const;
	const vector3df& getRotation() const;
	const vector3df& getScale() const;
	const core::aabbox3df getBoundingBox() const;
	const bool getVisible() const;
	const bool getActive() const;
	const int getIterations() const;
	//mutators
	void setPosition(const vector3df &position);
	void setRotation(const vector3df &rotation);
	void setScale(const vector3df &scale);
	void setVisible(const bool visible);
	void incrementIterations();

protected:
	E_OBJECT_COMPONENTS componentMask;
	//3d infomation
	std::wstring filename;
	scene::IAnimatedMeshSceneNode *mesh;

private:
	//whether the object is visible to the player
	bool visible;
	//whether the object should still exist
	bool active;
	int iterations;
	//iterator to this
	unsigned index;
};

#endif
