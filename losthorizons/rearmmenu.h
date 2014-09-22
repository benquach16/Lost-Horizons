#ifndef _REARMMENU_H_
#define _REARMMENU_H_


//because we need to make equipping fleet ships more intuitive
class RearmMenu
{
public:
	RearmMenu();
	~RearmMenu();

	void run();
protected:
	irr::gui::IGUIWindow *window;
	irr::gui::IGUIListBox *shipsInFleet;
	irr::gui::IGUiTreeView *equipmentTree;
	irr::gui::IGUIListBox *availableWeapons;
};

#endif
