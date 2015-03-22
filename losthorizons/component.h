#ifndef _COMPONENT_H_
#define _COMPONENT_H_

// a simple incremental list of the components
enum E_COMPONENT_TYPES
{
	DESCRIPTION,
	VISIBLE,
	POSITION,
	VELOCITY,
	FACTION,
	DESTRUCTIBLE,
	HEALTH,
	SHIELD,
	TARGET,
	TARGETABLE,
	COMPONENT_COUNT
};

// masks for each of the components
enum E_COMPONENT_MASKS
{
	COMPONENT_DESCRIPTION = 1 << DESCRIPTION,
	COMPONENT_VISIBLE = 1 << VISIBLE,
	COMPONENT_POSITION = 1 << POSITION,
	COMPONENT_VELOCITY = 1 << VELOCITY,
	COMPONENT_FACTION = 1 << FACTION,
	COMPONENT_DESTRUCTIBLE = 1 << DESTRUCTIBLE,
	COMPONENT_HEALTH = 1 << HEALTH,
	COMPONENT_SHIELD = 1 << SHIELD,
	COMPONENT_TARGET = 1 << TARGET,
	COMPONENT_TARGETABLE = 1 << TARGETABLE,
	ALL_COMPONENTS = (1 << COMPONENT_COUNT) - 1
};

namespace Component
{

	class Component
	{
	public:
		// for saving/loading
		//virtual void deserialize() = 0;
		//virtual void serialize() = 0;

		// do we need this?
		//vitrual void applyFromTemplate(Component template) = 0;
	};

}

#endif
