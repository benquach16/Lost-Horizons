#ifndef _MESSAGEMENU_H_
#define _MESSAGEMENU_H_

#include "menuwindow.h"
#include "globals.h"

using namespace base;

//this is a generic message box
class MessageMenu : public MenuWindow
{
public:
	enum MSGBOX_FLAG
	{
		CLOSE = 1,
		OKAY,
		YES = OKAY,
		NO = 4,
		YESNO = NO
	};

	MessageMenu(const rect<s32> &rectangle, gui::IGUIElement *parent = 0, const wchar_t *caption = 0, unsigned flags = OKAY, bool draggable = true, bool drawTitleBar = true, bool modal = true, s32 id = -1);
	~MessageMenu();

	int run();

	void setTimer(int timeout) { endTime = timeout > 0 ? timer->getTime() + timeout : 0; }
	void moveButtons(position2d<s32> &offset) { if (yes) yes->move(offset); if (no) no->move(offset); }
	void addText(position2d<s32> &pos, dimension2d<u32> &size, const wchar_t *text = 0, bool border = false) { guienv->addStaticText(text, rect<s32>(pos,size), border, true, window); }
	void addImage(video::ITexture *image, position2d<s32>& pos, bool useAlphaChannel = true) { guienv->addImage(image, pos, useAlphaChannel, window); }

private:
	unsigned endTime;
	gui::IGUIButton *close;
	gui::IGUIButton *yes;
	gui::IGUIButton *no;
};
#endif
