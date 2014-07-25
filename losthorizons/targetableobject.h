#ifndef _TARGETABLEOBJECT_H_
#define _TARGETABLEOBJECT_H_

#include "object.h"
#include "modelproperties.h"
#include "healthcomponent.h"

enum E_TARGETABLEOBJECT_TYPE
{
	TARGETABLEOBJECT_SHIP,
	TARGETABLEOBJECT_PLANET,
	TARGETABLEOBJECT_SPACESTATION,
	TARGETABLEOBJECT_PLAYER,
	TARGETABLEOBJECT_FIGHTER,
	TARGETABLEOBJECT_MISC
};


//we need to move a shitton of stuff to get save loading to work with this system
enum E_TARGETABLEOBJECT_COMPONENTS
{
	COMPONENT_DAMAGEABLE = 0x0001, //2^n
	COMPONENT_MOVEABLE = 0x0002,
	COMPONENT_FACTION = 0x0004,
	COMPONENT_CANTARGET = 0x0008
};

//object class in which player can target
class TargetableObject : public Object
{
public:
	//list of all available objects
	static std::vector<TargetableObject*> allTargets;
	//next available ID
	static u16 nextID;

	//parameterized constructor
	//constructor with a model properties
	TargetableObject(const u16 ID, const ModelProperties &modelProps, const vector3df &position, const vector3df &rotation,
		const E_GAME_FACTION faction);
	//raw constructor with all the other inputs
	TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale, const E_GAME_FACTION faction);
	virtual ~TargetableObject();
	virtual bool run();

	//overridable function designed to return specific information related to this object to the hud
	//virtual void information(gui::IGUIImage *targetBkg);

	//function to remove this from all targets
	void removeThisFromTargets();

	//mutators
	//void setFaction(const E_GAME_FACTION faction);
	//void setTargetable(bool targetable);
	void setComponentMask(E_TARGETABLEOBJECT_COMPONENTS components);
	void addComponentToMask(E_TARGETABLEOBJECT_COMPONENTS component);

	//some accessors
	const u16 getID() const;
	const wchar_t *getName() const;
	const wchar_t *getDesc() const;
	const wchar_t *getFactionName() const;
	const E_GAME_FACTION getFaction() const;
	const bool getTargetable() const;
	const vector2di& getScreenPosition() const;
	const E_TARGETABLEOBJECT_COMPONENTS getComponentMask() const;
	



	//pure virtual function to find out object type
	const virtual E_TARGETABLEOBJECT_TYPE getTargetableObjectType() const = 0;

protected:
	//need these for all targetable objects
	u16 ID;
	std::wstring name;
	std::wstring description;
	E_GAME_FACTION faction;
	E_TARGETABLEOBJECT_COMPONENTS componentMask;

	//for drawing targetting icons
	bool targetable;
	vector2di screenPosition;


private:
	//iterator to this
	unsigned index;
};
#endif
