#ifndef _OPTIONMENU_H_
#define _OPTIONMENU_H_

#include "menuwindow.h"
#include "irrlicht.h"

using namespace irr;
using namespace core;

//displays options to change config
class OptionMenu : public MenuWindow
{
public:
	OptionMenu(irr::IrrlichtDevice *graphics);
	~OptionMenu();

	void run();

	bool get(gui::IGUICheckBox *item);
	int get(gui::IGUIComboBox *item, const int* val);

private:
	int resY[8];
	int resX[8];
	gui::IGUIComboBox *resolution;
	//gui::IGUIComboBox *dynamicLighting;		to implement
	gui::IGUICheckBox *fullscreen;
	gui::IGUICheckBox *vsync;
	gui::IGUIButton *quit;
	gui::IGUIButton *apply;
};
#endif
