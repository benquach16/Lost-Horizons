#ifndef _REARMMENU_H_
#define _REARMMENU_H_

#include <irrlicht.h>
#include "fleet.h"
#include "turretproperties.h"
#include "objectmanager.h"

//we're going to use a slots system to let players choose what weapon goes in whichever slot
class WeaponSlot
{
public:
	WeaponSlot(E_TURRET_CLASS type, irr::core::vector2di position, int index);
	//since this uses videodriver draw2dimage you must call this every frame
	void draw();
	//boilerplate code
	bool getWithinBoundingBox(int offsetx, int offsety);
	const int getIndex() const;
	E_TURRET_CLASS getType() const;
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
	void reloadWeapons(Ship* ship);
	void run();
	//this refreshes the weapon positions on the RTT
	void equipWeapons();
protected:
	Ship* getSelectedShip();
	Fleet* fleet;
	int currentSelected;
	int currentSelectedSlot;
	irr::gui::IGUIWindow *window;
	irr::gui::IGUIListBox *shipsInFleet;
	irr::gui::IGUIImage *shipImage;
	irr::gui::IGUIButton *closeButton;
	irr::gui::IGUIButton *applyButton;
	irr::video::ITexture *rt;
	irr::scene::ICameraSceneNode *shipCamera;
	
	//irr::gui::IGUiTreeView *equipmentTree;
	irr::gui::IGUIListBox *availableWeapons;
	std::vector<ObjectManager::E_ITEM_LIST> availableWeaponsPair; // in sync with the list box
	irr::gui::IGUIStaticText* weaponTitle;
	irr::gui::IGUIStaticText *description;
	E_TURRET_CLASS selectedWeaponClass;
	std::vector<WeaponSlot> weaponImages;
};

#endif
