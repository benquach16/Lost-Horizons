#ifndef _KEYLISTENER_H_
#define _KEYLISTENER_H_

#include "irrlicht.h"

using namespace irr;

class KeyListener : public IEventReceiver
{
public:
	KeyListener();
	virtual bool OnEvent(const SEvent& event);
	virtual bool isKeyDown(EKEY_CODE keyCode) const;
	const int getMouseX() const;
	const int getMouseY() const;
	const int getMouseWheel() const;
	bool getLeftMouseButton() const;
	bool getRightMouseButton() const;

private:
	bool keys[irr::KEY_KEY_CODES_COUNT];
	bool mouseL;
	bool mouseR;
	int mouseX, mouseY;
	int mouseWheel;
};

#endif
