#ifndef _OBJECT_H_
#define _OBJECT_H_

#include <list>
#include <string>

#include "irrlicht.h"


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
		const vector3df &scale = vector3df(1,1,1), bool targetable = false);

	//instantiate with filename
	//irr::IrrlichtDevice *graphics = irrlicht device
	//const wchar_t *filename = filepath of the mesh
	Object(const wchar_t *filename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1), bool targetable = false);

	//parameterized constructor with texture overloading
	Object(const wchar_t *filename, const wchar_t *tfilename, const vector3df &position = vector3df(0,0,0),
		const vector3df &rotation = vector3df(0,0,0), const vector3df &scale = vector3df(1,1,1), bool targetable = false);

	//copy constructor
	Object(const Object *obj);
	//overloaded assignment operator
	Object& operator=(const Object *obj);


	//desctructor
	virtual ~Object();
	//meant to be overridden
	virtual void run(f32 frameDeltaTime);
	//meant for use by planets and ships to show ingame info
	virtual void information() {}
	//needed for changing resolution ingame
	//reloads the mesh
	void reloadMesh();
	//change the mesh to a new one
	void changeMesh(const wchar_t *filename);
	//set the diffuse map of the mesh
	void setTexture(video::ITexture *tex);

	//accessors
	//returns an rvalue
	const vector3df& getPosition() const;
	const vector3df& getRotation() const;
	const vector3df& getScale() const;
	const vector2di& getScreenPosition() const;
	const bool& isTargetable() const;
	//mutators
	void setPosition(const vector3df &newPosition);
	void setRotation(const vector3df &newRotation);
	void setScale(const vector3df &newScale);

protected:
	//if the object is targetable we want it to show up on the hud
	void setupTarget();
	//if player can select this object
	bool targetable;

	//basic info about object
	vector3df position;
	vector3df rotation;
	vector3df scale;

	//for targetable objects
	vector2di screenPosition;

	gui::IGUIImage *targetSquare;

	//3d infomation
	IAnimatedMeshSceneNode *mesh;
	std::wstring filename;

	//iterator to this
	std::list<Object*>::iterator it;

};

#endif
