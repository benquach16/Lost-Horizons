#ifndef _SPACESTATIONPROPERTIES_H_
#define _SPACESTATIONPROPERTIES_H_

#include "modelproperties.h"

//space station xml loading
class SpaceStationProperties : public ModelProperties
{
public:
	SpaceStationProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~SpaceStationProperties();

protected:
	//interpret text into bool
	bool getTrueOrFalse(const wchar_t *text);

	bool spawnShips;
	bool spawnFighters;
	bool serviceFitting;
	bool serviceJobBoard;
	bool serviceShipYard;
	float buyMarkupFactor;
	float sellMarkdownFactor;
	bool isHQ;
	unsigned shipSpawnTimer;
};


#endif
