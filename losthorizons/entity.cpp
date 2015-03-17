#include "stdafx.h"
#include <assert.h>
#include "entity.h"

Entity::EntityList Entity::allEntities;

Entity::EntityList::EntityList() : entityCount(0) {}
Component::Component *Entity::EntityList::getComponent(unsigned component)
{
	switch (component)
	{
	case HEALTH:
		return health;
	default:
		assert(true); // failed to return a valid component array
		return 0;
	}
}

unsigned Entity::createEntity(unsigned components)
{
	assert(allEntities.entityCount < MAX_ENTITY_COUNT); // caller should do bounds check
	allEntities.mask[allEntities.entityCount] = components;
	return allEntities.entityCount++;
}

void Entity::destroyEntity(unsigned entity)
{
	assert(allEntities.entityCount > 0); // caller should do bounds check
	allEntities.entityCount--;
	allEntities.mask[entity] = allEntities.mask[allEntities.entityCount];
	for (unsigned i = 0; i < COMPONENT_COUNT; ++i) {
		if (allEntities.mask[entity] & (1 << i)) {
			allEntities.getComponent(i)[entity] = allEntities.getComponent(i)[allEntities.entityCount];
		}
	}
}

unsigned Entity::createShip( ) // TODO: define once more components are implemented
{
	unsigned entity = createEntity(COMPONENT_VISIBLE | COMPONENT_POSITION);
	//allEntities.visible[entity] = someMeshAndShit;
	//allEntities.position[entity] = thePosition;
	return entity;
}

unsigned Entity::createStation( ) // TODO: incomplete
{
	// should be defined similarly to createShip
	return 0;
}
