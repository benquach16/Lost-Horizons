#include "stdafx.h"
#include "intercom.h"
#include "globals.h"
#include <iostream>

using namespace base;

#define MESSAGELENGTH 5000

Intercom::Intercom()
	: listBox(0), tabs(0), lastPosted(0), endTime(0)
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
	if (listBox->getItemCount() > 8)
	{
		listBox->removeItem(0);
	}
	if (timer->getTime() > endTime)
	{
		listBox->removeItem(0);
		endTime = timer->getTime() + MESSAGELENGTH;
	}
}

void Intercom::postMessage(const wchar_t *text)
{
	//make sure we cant repeat text over and over
	for (unsigned i = 0; i < listBox->getItemCount(); ++i)
	{
		if (*listBox->getListItem(i) == *text && timer->getTime() < lastPosted + MESSAGELENGTH - 1000)
		{
			return;
		}
	}
	listBox->addItem(text);
	lastPosted = timer->getTime();
	endTime = lastPosted + MESSAGELENGTH;
}
