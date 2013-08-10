#ifndef _TARGETABLEOBJECT_H_
#define _TARGETABLEOBJECT_H_

#include "object.h"
#include "modelproperties.h"

//object class in which player can target
class TargetableObject : public Object
{
public:
	//list of all available objects
	static std::list<TargetableObject*> allTargets;
	//default constructor
	TargetableObject();
	//parameterized constructor
	//constructor with a model properties
	TargetableObject(const ModelProperties &modelProps, const vector3df &position, const vector3df &rotation);
	//raw constructor with all the other inputs
	TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale);
	~TargetableObject();
	virtual void run(f32 frameDeltaTime);
	//overridable function designed to return specific information related to this object to the hud
	//virtual void information(gui::IGUIImage *targetBkg);

	//some accessors
	const std::wstring& getName() const;
	const std::wstring& getDesc() const;
	const vector2di& getScreenPosition() const;

protected:
	//ingame name and description of this object
	//need this for all targetable objects
	std::wstring name;
	std::wstring description;

	//for creating a 2d hud icon for the targetable object
	vector2di screenPosition;
	gui::IGUIImage *targetSquare;

	//iterator to this
	std::list<TargetableObject*>::iterator it;
};


#endif
