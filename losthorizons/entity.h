#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "healthcomponent.h"

// each component type is laid out contiguously in memory to
// improve cache coherency and facilitate iteration
class Entity
{
public:
	static const unsigned MAX_ENTITY_COUNT = 1024;
	static struct EntityList
	{
		unsigned mask[MAX_ENTITY_COUNT];
		Component::Health health[MAX_ENTITY_COUNT];
		unsigned entityCount;
		EntityList();
		Component::Component *getComponent(unsigned component);
	} allEntities; // to replace allObjects
	
	static unsigned createEntity(unsigned components);
	static void destroyEntity(unsigned entity);

	static unsigned createShip( );
	static unsigned createStation( );
};

#endif
