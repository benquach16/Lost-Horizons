#ifndef _REARMMENU_H_
#define _REARMMENU_H_

#include <irrlicht.h>
#include "fleet.h"
#include "turretproperties.h"

//we're going to use a slots system to let players choose what weapon goes in whichever slot
class WeaponSlot
{
public:
	WeaponSlot(E_TURRET_CLASS type, irr::core::vector2di position, int index);
	void draw();
	bool getWithinBoundingBox(int offsetx, int offsety);
	const int getIndex() const;
protected:
	int index;
	irr::core::stringc texture;
	irr::core::vector2di position;
	E_TURRET_CLASS type;
};

//because we need to make equipping fleet ships more intuitive
class RearmMenu
{
public:
	RearmMenu();
	~RearmMenu();

	void loadFleet(const Fleet* fleet);
	void reloadShip(Ship *ship);
	void run();
	void equipWeapons();
protected:
	Fleet* fleet;
	int currentSelected;
	int currentSelectedSlot;
	irr::gui::IGUIWindow *window;
	irr::gui::IGUIListBox *shipsInFleet;
	irr::gui::IGUIImage *shipImage;
	irr::gui::IGUIButton *closeButton;
	irr::video::ITexture *rt;
	irr::scene::ICameraSceneNode *shipCamera;
	
	//irr::gui::IGUiTreeView *equipmentTree;
	irr::gui::IGUIListBox *availableWeapons;
	irr::gui::IGUIStaticText *description;
	std::vector<WeaponSlot> weaponImages;
};

#endif
