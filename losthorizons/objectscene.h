#ifndef _OBJECTSCENE_H_
#define _OBJECTSCENE_H_

#include <vector>
#include "object.h"
#include "targetableobject.h"
#include "ship.h"
#include "spacestation.h"
#include "fighter.h"

//Object Scene
//This is in preperation for the conversion of the game to use octrees
//The GameScene class will no longer run object management, only will handle the game background/scene information
//this will handle all objects
class ObjectScene
{
public:
	ObjectScene();
	ObjectScene(const ObjectScene &s);
	~ObjectScene();

	void run();
	void clear();
protected:
	std::vector<ObjectScene*> childScenes;
	std::vector<Object*> objectsInScene;
	ObjectScene *parent;
};

#endif
