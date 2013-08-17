#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <list>
#include <string>

#include "irrlicht.h"
#include "callback.h"


using namespace irr;
using namespace core;
using namespace scene;

//all objects are associated with a faction
enum E_GAME_FACTIONS
{
	E_FACTION_TERRAN,
	E_FACTION_PROVIAN,
	E_FACTION_PIRATE,
	E_FACTION_NEUTRAL
};

//This is the base class of all renderable (3d really) objects in the game
class Object
{
public:
	static std::list<Object*> allObjects;
	//default constructor
	Object();

	//parametrized constructors
	//instantiate with position, rotation, etc
	Object(scene::IAnimatedMesh *m, const vector3df &position = vector3df(0,0,0), const vector3df &rotation = vector3df(0,0,0),
		const vector3df &scale = vector3df(1,1,1));

	//instantiate with filename
	//irr::IrrlichtDevice *graphics = irrlicht device
	//const wchar_t *filename = filepath of the mesh
	Object(const wchar_t *filename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));

	//parameterized constructor with texture overloading
	Object(const wchar_t *filename, const wchar_t *tfilename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1));

	//copy constructor
	Object(const Object *obj);
	//overloaded assignment operator
	Object& operator=(const Object *obj);


	//desctructor
	virtual ~Object();
	//meant to be overridden
	virtual void run(f32 frameDeltaTime);
	//meant for use by planets and ships to show ingame info
	//moved to targetable object class
	//virtual void information() {}
	//needed for changing resolution ingame
	//reloads the mesh
	void reloadMesh();
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
	IAnimatedMeshSceneNode *mesh;
	std::wstring filename;

	//iterator to this
	std::list<Object*>::iterator it;
};

#endif
