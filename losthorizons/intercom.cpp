#include "stdafx.h"
#include "intercom.h"
#include "globals.h"
#include <iostream>

using namespace base;

Intercom::Intercom(Player *player) : player(player), listBox(0), tabs(0), deleteTimer(0)
{
	listBox = guienv->addListBox(rect<s32>(width-300, height-180, width, height));
	listBox->setAutoScrollEnabled(true);

}

Intercom::~Intercom()
{
	listBox->remove();
}

void Intercom::run()
{
	//make sure we delete old messages
	if(listBox->getItemCount() > 8)
	{
		listBox->removeItem(0);
	}
	if(deleteTimer < timer->getTime())
	{
		listBox->removeItem(0);
		deleteTimer = timer->getTime() + 5000;
	}
	if(player->getInfo().shield < 10)
	{
		addText(L"Sir, our shields are down");
	}
}

void Intercom::addText(const wchar_t *text)
{
	//make sure we cant repeat text over and over
	for(u32 i = 0; i < listBox->getItemCount(); ++i)
	{
		if(*listBox->getListItem(i) == *text)
		{
			return;
		}
	}
	listBox->addItem(text);
	deleteTimer = timer->getTime() + 5000;

}
