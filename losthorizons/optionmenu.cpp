#include "stdafx.h"
#include "optionmenu.h"
#include "config.h"
#include <string>
#include <cmath>


//setup GUI and initialize variables
OptionMenu::OptionMenu(irr::IrrlichtDevice *graphics)
	: MenuWindow()
{
	dimension2d<u32> t;
	t = graphics->getVideoDriver()->getScreenSize();
	//create window
	window = graphics->getGUIEnvironment()->addWindow(rect<s32>(t.Width/2-300, t.Height/2-200, t.Width/2+300, t.Height/2+200), true, L"Options");
	window->setDraggable(false);
	window->setDrawTitlebar(false);
	window->getCloseButton()->setVisible(false);

	quit = graphics->getGUIEnvironment()->addButton(rect<s32>(480,360,580,380), window,-1, L"Close");
	apply = graphics->getGUIEnvironment()->addButton(rect<s32>(360,360,460,380), window,-1, L"Apply");

	resY[1] = 720;
	resY[2] = 768;
	resY[3] = 900;
	resY[4] = 960;
	resY[5] = 1024;
	resY[6] = 1050;
	resY[7] = 1080;

	//create resolution menu
	graphics->getGUIEnvironment()->addStaticText(L"Resolution", rect<s32>(20,20,120,40), false ,true, window);
	resolution = graphics->getGUIEnvironment()->addComboBox(rect<s32>(20,40,120,60), window);

	resY[0] = GetSystemMetrics(SM_CYSCREEN);
	resX[0] = GetSystemMetrics(SM_CXSCREEN);
	double monitorRatio = resX[0] / resY[0];
	resolution->addItem(L"native");

	std::string temp(" x ");
	std::wstring x(temp.begin(), temp.end());
	std::wstring option;
	for (unsigned i = 1; i < 8; ++i) {
		if (gConfig.iResolutionY == resY[i]) {
			resolution->setSelected(i);
		}
		if (resY[i] < resY[0]) {
			resX[i] = static_cast<int>(ceil(resY[i] * monitorRatio));
			option = std::to_wstring(resX[i]) + x + std::to_wstring(resY[i]);
			resolution->addItem(option.c_str());
		}
	}

	graphics->getGUIEnvironment()->addStaticText(L"Fullscreen", rect<s32>(50,320,150,340), false, true, window);
	fullscreen = graphics->getGUIEnvironment()->addCheckBox(gConfig.bFullScreen, rect<s32>(20,320,40,340), window);
	graphics->getGUIEnvironment()->addStaticText(L"V-sync", rect<s32>(200,320,260,340), false, true, window);
	vsync = graphics->getGUIEnvironment()->addCheckBox(gConfig.bVsync, rect<s32>(170,320,190,340), window);
}

OptionMenu::~OptionMenu()
{
}

void OptionMenu::restart()
{
	for (unsigned i = 1; i < 8; ++i) {
		if (gConfig.iResolutionY == resY[i]) {
			resolution->setSelected(i);
		}
	}
	fullscreen->setChecked(gConfig.bFullScreen);
	vsync->setChecked(gConfig.bVsync);
}

void OptionMenu::run()
{
	//ensure menu is hidden or not hidden
	MenuWindow::run();
	if (quit->isPressed()) {
		restart();
		window->setVisible(false);
	}
	if (apply->isPressed()) {
		gConfig.iResolutionX = get(resolution, resX);
		gConfig.iResolutionY = get(resolution, resY);
		gConfig.bFullScreen = get(fullscreen);
		gConfig.bVsync = get(vsync);
		window->setVisible(false);
	}
}

bool OptionMenu::get(gui::IGUICheckBox *item)
{
	return item->isChecked() ? true : false;
}

int OptionMenu::get(gui::IGUIComboBox *item, const int* val)
{
	return val[item->getSelected()];
}
