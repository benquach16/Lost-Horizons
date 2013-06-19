#include "stdafx.h"
#include "keylistener.h"

KeyListener::KeyListener() : mouseL(false), mouseR(false), mouseX(0), mouseY(0),
	mouseWheel(0)
{
	for(unsigned i = 0; i < irr::KEY_KEY_CODES_COUNT; i++)
	{
		keys[i] = false;
	}

}

bool KeyListener::OnEvent(const SEvent& event)
{
	//get events from operating system
    if(event.EventType == irr::EET_KEY_INPUT_EVENT)
        keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
	if(event.EventType == irr::EET_MOUSE_INPUT_EVENT)
	{
		//mouse events
		if(event.MouseInput.Event == irr::EMIE_LMOUSE_PRESSED_DOWN)
		{
			mouseL = true;
		}
		if(event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
		{
			mouseR = true;
		}
		if(event.MouseInput.Event==irr::EMIE_MOUSE_MOVED)
		{
			// check the mouse coords
			mouseX = event.MouseInput.X;
			mouseY = event.MouseInput.Y;
		}
	}
    return false;
}

bool KeyListener::isKeyDown(EKEY_CODE keyCode) const
{
	return keys[keyCode];
}

const int KeyListener::getMouseX() const
{
	return mouseX;
}

const int KeyListener::getMouseY() const
{
	return mouseY;
}