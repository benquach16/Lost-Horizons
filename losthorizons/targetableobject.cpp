#include "stdafx.h"
#include "targetableobject.h"

std::list<TargetableObject*> TargetableObject::allTargets;
u16 TargetableObject::nextID(0);

TargetableObject::TargetableObject()
{
}

TargetableObject::TargetableObject(u16 ID, const ModelProperties& modelProps, const vector3df &position, const vector3df &rotation,
								   const E_GAME_FACTION faction)
	: Object(modelProps.getFilename().c_str(), position, rotation, modelProps.getScale()),
	  ID(ID), name(modelProps.getName()), description(modelProps.getDesc()), faction(faction)
{
	allTargets.push_front(this);
	it = allTargets.begin();
}

TargetableObject::TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale, const E_GAME_FACTION faction)
		: Object(filename, position, rotation, scale), faction(faction), name(name), description(description)
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
	if(faction == FACTION_PIRATE)
		vdriver->draw2DImage(vdriver->getTexture("res/menu/target_array_enemy.png"), screenPosition - vector2di(32), rect<s32>(0,0,64,64), 0, SColor(255,255,255,255), true);
	else
		vdriver->draw2DImage(vdriver->getTexture("res/menu/target_array.png"), screenPosition - vector2di(32), rect<s32>(0,0,64,64), 0, SColor(255,255,255,255), true);
}

const u16 TargetableObject::getID() const
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

const E_GAME_FACTION TargetableObject::getFaction() const
{
	return faction;
}
