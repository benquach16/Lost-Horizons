#ifndef _KEYLISTENER_H_
#define _KEYLISTENER_H_

#include "stdafx.h"

using namespace irr;

enum E_KEY_STATE
{
	KEY_DOWN,
	KEY_UP,
	KEY_RELEASED
}; //currently unused

class KeyListener : public IEventReceiver
{
public:
	KeyListener();
	virtual bool OnEvent(const SEvent& event);
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	bool isKeyReleased(EKEY_CODE keyCode);
	bool isKeyPressed(EKEY_CODE keyCode);
	const int getMouseX() const;
	const int getMouseY() const;
	const int getMouseWheel() const;
	bool getLeftMouseButton() const;
	bool getRightMouseButton() const;

private:
	bool keys[KEY_KEY_CODES_COUNT];
	bool keysReleased[KEY_KEY_CODES_COUNT];
	int keysRepeatCount[KEY_KEY_CODES_COUNT];
	int mouseX, mouseY;
	int mouseWheel;
};

#endif
