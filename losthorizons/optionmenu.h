#ifndef _OPTIONMENU_H_
#define _OPTIONMENU_H_

#include "menuwindow.h"

using namespace irr;
using namespace core;

//displays options to change config
class OptionMenu : public MenuWindow
{
public:
	OptionMenu(gui::IGUIWindow *menu);
	~OptionMenu();

	void restart();
	void run();

	bool get(gui::IGUICheckBox *item);
	int get(gui::IGUIComboBox *item, const int* val);

private:
	int resY[9];
	int resX[9];
	gui::IGUIComboBox *resolution;
	//gui::IGUIComboBox *dynamicLighting;		to implement
	gui::IGUICheckBox *fullscreen;
	gui::IGUICheckBox *vsync;
	gui::IGUIButton *close;
	gui::IGUIButton *confirm;
};
#endif
