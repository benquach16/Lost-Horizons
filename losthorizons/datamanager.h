#ifndef _DATAMANAGER_H_
#define _DATAMANAGER_H_

#include "gamescenemanager.h"
#include "player.h"

class DataManager
{
public:
	struct ShipData
	{
		u16 ID, target;
		vector3df position, rotation;
		ShipInformation info;
		//std::vector<TurretData> mediumTurrets;
		bool targetting;
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
	E_GAME_SCENE scene;
	std::deque<ShipData> ships;
	std::stack< std::pair<bool,u16> > shipTargets;
	std::list<TargetableObject*> *targets;

	void setShipTargets();
};

#endif
