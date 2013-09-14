#include "stdafx.h"
#include "intercom.h"
#include <iostream>

Intercom::Intercom(Player *player) : player(player), listBox(0), tabs(0)
{
	listBox = guienv->addListBox(rect<s32>(iWidth-300, iHeight-180, iWidth, iHeight));
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
	if(player->getInfo().shield < 10)
	{
		addText(L"Sir, our shields are down");
	}
}

void Intercom::addText(const wchar_t *text)
{
	//make sure we cant repeat text over and over
	const wchar_t *tmp =listBox->getListItem(listBox->getItemCount()-1);
	//we have to dereference this to properly compare
	if(!tmp)
	{
		listBox->addItem(text);
	}
	else if(*tmp != *text)
	{
		std::cout <<tmp <<std::endl;
		listBox->addItem(text);
	}
}
