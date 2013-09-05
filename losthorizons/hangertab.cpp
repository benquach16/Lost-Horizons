#include "stdafx.h"
#include "hangertab.h"

HangerTab::HangerTab(gui::IGUITabControl *tabs) : MenuTab()
{
	tab = tabs->addTab(L"Hanger");
	//add hanger stuff

}

HangerTab::~HangerTab()
{

}

void HangerTab::run()
{

}
