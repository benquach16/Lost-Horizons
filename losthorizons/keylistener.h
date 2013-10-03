#ifndef _KEYLISTENER_H_
#define _KEYLISTENER_H_

#include "irrlicht.h"

using namespace irr;

enum E_KEY_STATE
{
	KEY_DOWN,
	KEY_UP,
	KEY_RELEASED
};

class KeyListener : public IEventReceiver
{
public:
	KeyListener();
	virtual bool OnEvent(const SEvent& event);
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	bool isKeyReleased(EKEY_CODE keyCode);
	const int getMouseX() const;
	const int getMouseY() const;
	const int getMouseWheel() const;
	bool getLeftMouseButton() const;
	bool getRightMouseButton() const;

private:
	bool keys[irr::KEY_KEY_CODES_COUNT];
	bool keysReleased[irr::KEY_KEY_CODES_COUNT];
	bool mouseL;
	bool mouseR;
	int mouseX, mouseY;
	int mouseWheel;
};

#endif
