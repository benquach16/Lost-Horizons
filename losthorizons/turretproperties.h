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
	//default constructor
	TurretProperties();
	//load from file
	TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	//make sure we have a valid copy constructor so we can copy
	~TurretProperties();

	const int& getMaxTurn() const;
	const int& getDamage() const;
	const f32& getReloadSpeed() const;
	const int& getRange() const;
	const int& getProjectileSpeed() const;

	const std::wstring& getProjectileTex() const;
	const std::string& getSoundFilename() const;
	const core::vector3df& getProjectileScale() const;

	const E_TURRET_CLASS getTurretClass() const;
protected:
	E_TURRET_CLASS getTurretClass(const std::wstring &str);
	E_TURRET_CLASS turretClass;
	int turnSpeed;
	int damage;
	int range;
	int projectileSpeed;
	core::vector3df projectileScale;
	std::wstring projectileTexture;
	std::string soundFilename;
	f32 reloadSpeed;
};

//overloaded comparision operator
inline bool operator==(const TurretProperties &lhs, const TurretProperties &rhs)
{
	if(lhs.getName() == rhs.getName())
		return true;
	return false;
}


#endif
