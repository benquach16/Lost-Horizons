#ifndef _ENTITY_H_
#define _ENTITY_H_

#include "descriptioncomponent.h"
#include "visiblecomponent.h"
#include "positioncomponent.h"
#include "velocitycomponent.h"
#include "factioncomponent.h"
#include "destructiblecomponent.h"
#include "healthcomponent.h"
#include "shieldcomponent.h"
#include "targetcomponent.h"
#include "targetablecomponent.h"

// each component type is laid out contiguously in memory to
// improve cache coherency and facilitate iteration
class Entity
{
public:
	static const unsigned MAX_ENTITY_COUNT = 512;
	static struct EntityList
	{
		unsigned mask[MAX_ENTITY_COUNT];
		Component::Description description[MAX_ENTITY_COUNT];
		Component::Visible visible[MAX_ENTITY_COUNT];
		Component::Position position[MAX_ENTITY_COUNT];
		Component::Velocity velocity[MAX_ENTITY_COUNT];
		Component::Faction faction[MAX_ENTITY_COUNT];
		//Component::Destructible destructible[MAX_ENTITY_COUNT];
		Component::Health health[MAX_ENTITY_COUNT];
		Component::Shield shield[MAX_ENTITY_COUNT];
		Component::Target target[MAX_ENTITY_COUNT];
		Component::Targetable targetable[MAX_ENTITY_COUNT];
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
