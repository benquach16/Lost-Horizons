#ifndef _TURRETPROPERTIES_H_
#define _TURRETPROPERTIES_H_

#include "modelproperties.h"

enum E_TURRET_CLASS
{
	E_CLASS_LIGHT,
	E_CLASS_MEDIUM,
	E_CLASS_HEAVY,
	E_CLASS_PD
};

//for turrets
class TurretProperties : public ModelProperties
{
public:
	//default constructor
	TurretProperties();
	//load from file
	TurretProperties(irr::IrrlichtDevice *graphics, const std::string &f);
	~TurretProperties();

	const int& getMaxTurn() const;
	const int& getDamage() const;
	const f32& getReloadSpeed() const;
	const int& getRange() const;
	const int& getProjectileSpeed() const;

	const std::wstring& getProjectileTex() const;
	const core::vector3df& getProjectileScale() const;
protected:
	E_TURRET_CLASS getTurretClass(const std::wstring &str);
	E_TURRET_CLASS turretClass;
	int turnSpeed;
	int damage;
	int range;
	int projectileSpeed;
	core::vector3df projectileScale;
	std::wstring projectileTexture;
	f32 reloadSpeed;
};


#endif
