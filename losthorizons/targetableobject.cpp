#include "stdafx.h"
#include "targetableobject.h"

std::list<TargetableObject*> TargetableObject::allTargets;

TargetableObject::TargetableObject()
{
}

TargetableObject::TargetableObject(const ModelProperties& modelProps, const vector3df &position, const vector3df &rotation) : 
	Object(modelProps.getFilename().c_str(), position, rotation, modelProps.getScale()), name(modelProps.getName()), description(modelProps.getDesc())
{
	screenPosition = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getPosition(), scenemngr->getActiveCamera());
	targetSquare = guienv->addImage(vdriver->getTexture("res/menu/target_array.png"),screenPosition);
	allTargets.push_front(this);
	it = allTargets.begin();
}

TargetableObject::TargetableObject(const std::wstring& name, const std::wstring &description, const wchar_t *filename,
		const vector3df &position, const vector3df &rotation, const vector3df &scale) : 
Object(filename, position, rotation, scale)
{
	screenPosition = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getPosition(), scenemngr->getActiveCamera());
	targetSquare = guienv->addImage(vdriver->getTexture("res/menu/target_array.png"),screenPosition);
	allTargets.push_front(this);
	it = allTargets.begin();
}

TargetableObject::~TargetableObject()
{
}

void TargetableObject::run(f32 frameDeltaTime)
{
	Object::run(frameDeltaTime);
	//update 2d position of this object
	screenPosition = scenemngr->getSceneCollisionManager()->getScreenCoordinatesFrom3DPosition(getPosition(), scenemngr->getActiveCamera());
	targetSquare->setRelativePosition(vector2d<s32>(screenPosition.X-32,screenPosition.Y-32));
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
