#ifndef _FACTIONCOMPONENT_H_
#define _FACTIONCOMPONENT_H_

#include "component.h"

enum E_GAME_FACTION
{
	FACTION_TERRAN,
	FACTION_PROVIAN,
	FACTION_PIRATE,
	FACTION_NEUTRAL
};

namespace Component {

	class Faction : public Component
	{
	public:
		E_GAME_FACTION currentFaction;
	};

}

#endif
