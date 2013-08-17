#include "stdafx.h"
#include "targetableobject.h"

std::list<TargetableObject*> TargetableObject::allTargets;
u32 TargetableObject::nextID(0);

TargetableObject::TargetableObject()
{
}

TargetableObject::TargetableObject(u32 ID, const ModelProperties& modelProps, const vector3df &position, const vector3df &rotation)
	: Object(modelProps.getFilename().c_str(), position, rotation, modelProps.getScale()),
	  ID(ID), name(modelProps.getName()), description(modelProps.getDesc())
{
	allTargets.push_front(this);
	it = allTargets.begin();
}

TargetableObject::TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale)
		: Object(filename, position, rotation, scale)
{
	allTargets.push_front(this);
	it = allTargets.begin();
}

TargetableObject::~TargetableObject()
{
	allTargets.erase(it);
}

void TargetableObject::run(f32 frameDeltaTime)
{
	Object::run(frameDeltaTime);
	//update 2d position of this object
	screenPosition = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getPosition(), scenemngr->getActiveCamera());
	//draw a 2d target array on this object
	vdriver->draw2DImage(vdriver->getTexture("res/menu/target_array.png"), screenPosition - vector2di(32), rect<s32>(0,0,64,64), 0, SColor(255,255,255,255), true);
}

const u32 TargetableObject::getID() const
{
	return ID;
}

const std::wstring& TargetableObject::getName() const
{
	return name;
}

const std::wstring& TargetableObject::getDesc() const
{
	return description;
}

const vector2di& TargetableObject::getScreenPosition() const
{
	return screenPosition;
}
