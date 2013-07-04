#ifndef _TURRETPROPERTIES_H_
#define _TURRETPROPERTIES_H_

#include "itemproperties.h"

class TurretProperties : public ItemProperties
{
public:
	TurretProperties();
	TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~TurretProperties();

protected:
	int maxTurn;
	int reloadSpeed;
};


#endif
