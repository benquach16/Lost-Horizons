#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "gamescenemanager.h"
#include "turret.h"
#include "ship.h"

class DataManager
{
public:
	struct ShipData
	{
		vector3df position, rotation;
		ShipInformation info;
		//std::vector<TurretData> mediumTurrets;
		//u32 shipTarget;
	};
	struct TurretData
	{
		E_TURRET_CLASS turretClass;
		s32 turnSpeed, damage, range, projectileSpeed;
		f32 reloadSpeed;
	}; // will move this later

	void pull();
	void push();
	void save(const std::string &filename);
	void load(const std::string &filename);

private:
	E_GAMESCENES scene;
	std::vector<ShipData> ships;
};

#endif
