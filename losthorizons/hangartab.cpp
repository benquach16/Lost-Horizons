#include "stdafx.h"
#include "hangartab.h"

HangarTab::HangarTab(gui::IGUITabControl *tabs) : MenuTab()
{
	tab = tabs->addTab(L"Hangar");
	//add hangar stuff

}

HangarTab::~HangarTab()
{

}

void HangarTab::run()
{

}
