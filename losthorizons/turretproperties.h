#ifndef _TURRETPROPERTIES_H_
#define _TURRETPROPERTIES_H_

#include "modelproperties.h"

enum E_TURRET_CLASS
{
	TURRET_HEAVY,
	TURRET_MEDIUM,
	TURRET_LIGHT,
	TURRET_PD
};

//for turrets
class TurretProperties : public ModelProperties
{
public:
	//load from file
	TurretProperties(const std::string &f);
	//make sure we have a valid copy constructor so we can copy
	~TurretProperties();

	const int& getMaxTurn() const;
	const int& getDamage() const;
	const f32& getReloadSpeed() const;
	const int& getRange() const;
	const int& getProjectileSpeed() const;
	const int getEnergyUse() const;

	const wchar_t *getProjectileTex() const;
	const char *getSoundFilename() const;
	const core::vector3df& getProjectileScale() const;

	const E_TURRET_CLASS getTurretClass() const;

protected:
	E_TURRET_CLASS getTurretClass(const std::wstring &str);
	E_TURRET_CLASS turretClass;
	int turnSpeed;
	int damage;
	int range;
	int energyUse;
	int projectileSpeed;
	core::vector3df projectileScale;
	std::wstring projectileTexture;
	std::string soundFilename;
	f32 reloadSpeed;
};

//overloaded comparision operator
inline bool operator==(const TurretProperties &lhs, const TurretProperties &rhs)
{
	return wcscmp(lhs.getName(), rhs.getName()) == 0;
}

#endif
