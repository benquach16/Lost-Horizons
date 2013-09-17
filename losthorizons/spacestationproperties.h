#ifndef _SPACESTATIONPROPERTIES_H_
#define _SPACESTATIONPROPERTIES_H_

#include "modelproperties.h"

//space station xml loading
class SpaceStationProperties : public ModelProperties
{
public:
	SpaceStationProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~SpaceStationProperties();

	//accessors
	const bool getSpawnShips() const;
	const bool getSpawnFighters() const;

	const bool getServiceFitting() const;
	const bool getServiceJobBoard() const;
	const bool getServiceShipYard() const;

	const float getBuyMarkupFactor() const;
	const float getSellMarkdownFactor() const;

	const bool getIsHQ() const;
	const unsigned getShipSpawnTimer() const;

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
