#ifndef _TARGETABLEOBJECT_H_
#define _TARGETABLEOBJECT_H_

#include "object.h"
#include "modelproperties.h"

enum E_TARGETABLEOBJECT_TYPE
{
	E_OBJECT_SHIP,
	E_OBJECT_PLANET,
	E_OBJECT_SPACESTATION
};

//object class in which player can target
class TargetableObject : public Object
{
public:
	//list of all available objects
	static std::list<TargetableObject*> allTargets;
	//next available ID
	static u32 nextID;

	//default constructor
	TargetableObject();
	//parameterized constructor
	//constructor with a model properties
	TargetableObject(u32 ID, const ModelProperties &modelProps, const vector3df &position, const vector3df &rotation,
		const E_GAME_FACTIONS& faction);
	//raw constructor with all the other inputs
	TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale, const E_GAME_FACTIONS& faction);
	virtual ~TargetableObject();
	virtual void run(f32 frameDeltaTime);
	//overridable function designed to return specific information related to this object to the hud
	//virtual void information(gui::IGUIImage *targetBkg);
	//mutators
	void setFactionTo(const E_GAME_FACTIONS& faction);

	//some accessors
	const u32 getID() const;
	const std::wstring& getName() const;
	const std::wstring& getDesc() const;
	const vector2di& getScreenPosition() const;

	//pure virtual function to find out object type
	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const = 0;

protected:
	//need these for all targetable objects
	u32 ID;
	std::wstring name;
	std::wstring description;
	E_GAME_FACTIONS faction;

	//for drawing targetting icons
	vector2di screenPosition;

	//iterator to this
	std::list<TargetableObject*>::iterator it;
};
#endif
