#ifndef _REARMMENU_H_
#define _REARMMENU_H_

#include <irrlicht.h>
#include "fleet.h"

//because we need to make equipping fleet ships more intuitive
class RearmMenu
{
public:
	RearmMenu();
	~RearmMenu();

	void loadFleet(const Fleet* fleet);
	void run();
protected:
	irr::gui::IGUIWindow *window;
	irr::gui::IGUIListBox *shipsInFleet;
	irr::gui::IGUIImage *shipImage;
	irr::video::ITexture *rt;
	irr::scene::ICameraSceneNode *shipCamera;
	
	//irr::gui::IGUiTreeView *equipmentTree;
	irr::gui::IGUIListBox *availableWeapons;
	irr::gui::IGUIStaticText *description;
};

#endif
