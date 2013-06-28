#ifndef _MESSAGEMENU_H_
#define _MESSAGEMENU_H_

#include "menuwindow.h"

using namespace irr;
using namespace core;

//this is a generic message box
class MessageMenu : public MenuWindow
{
public:
	enum FLAGS
	{
		MM_NULL,
		MM_CLOSE,
		MM_OKAY,
		MM_YES = MM_OKAY,
		MM_NO = 4,
		MM_YESNO = MM_NO
	};

	MessageMenu(const rect<s32> &rectangle, const wchar_t *caption = 0, FLAGS flags = MM_OKAY, gui::IGUIElement *parent = 0, bool modal = true, s32 id = -1);
	~MessageMenu();

	int run();
	
	void setDraggable(bool draggable) { window->setDraggable(draggable); }
	void setDrawTitlebar(bool draw) { window->setDrawTitlebar(draw); }
	void addText(position2d<s32> &pos, dimension2d<u32> &size, const wchar_t *text = 0) { guienv->addStaticText(text, rect<s32>(UpperLeft+pos,size), false, true, window); }
	void addText(rect<s32> &rectangle, const wchar_t *text = 0) { guienv->addStaticText(text, rectangle, false, true, window); }
	void addImage(video::ITexture *image, position2d<s32>& pos, bool useAlphaChannel = true) { guienv->addImage(image, UpperLeft+pos, useAlphaChannel, window); }

protected:
	position2d<s32> UpperLeft;
	position2d<s32> LowerRight;

private:
	gui::IGUIButton *close;
	gui::IGUIButton *yes;
	gui::IGUIButton *no;
};
#endif
