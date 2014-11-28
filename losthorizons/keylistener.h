#ifndef _KEYLISTENER_H_
#define _KEYLISTENER_H_

#include "stdafx.h"

using namespace irr;

class KeyListener : public IEventReceiver
{
public:
	KeyListener();
	virtual bool OnEvent(const SEvent& event);
	const bool isKeyDown(EKEY_CODE keyCode) const;
	const bool isKeyUp(EKEY_CODE keyCode) const;
	const bool isKeyReleased(EKEY_CODE keyCode);
	const bool isKeyPressed(EKEY_CODE keyCode);
	const EKEY_CODE getKey();
	const char getChar();
	const int getMouseX() const;
	const int getMouseY() const;
	const int getMouseWheel() const;

private:
	enum E_KEY_STATE
	{
		KEY_STATE_PRESSED,
		KEY_STATE_DOWN,
		KEY_STATE_UP,
		KEY_STATE_RELEASED
	};

	E_KEY_STATE keys[KEY_KEY_CODES_COUNT];
	EKEY_CODE key;
	unsigned ch;
	int mouseX, mouseY;
	int mouseWheel;
};

#endif
