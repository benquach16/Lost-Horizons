//#include "stdafx.h"
#include "keylistener.h"

KeyListener::KeyListener() : 
	mouseL(false), mouseR(false), mouseX(0), mouseY(0), mouseWheel(0)
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
		if(event.MouseInput.Event == irr::EMIE_LMOUSE_LEFT_UP)
		{
			mouseL = false;
		}
		if(event.MouseInput.Event == irr::EMIE_RMOUSE_PRESSED_DOWN)
		{
			mouseR = true;
		}
		if(event.MouseInput.Event == irr::EMIE_RMOUSE_LEFT_UP)
		{
			mouseR = false;
		}
		if(event.MouseInput.Event==irr::EMIE_MOUSE_MOVED)
		{
			// check the mouse coords
			mouseX = event.MouseInput.X;
			mouseY = event.MouseInput.Y;
		}
		if(event.MouseInput.Event==irr::EMIE_MOUSE_WHEEL)
		{
			// how do i make it work?
			mouseWheel += (int)event.MouseInput.Wheel;
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

const int KeyListener::getMouseWheel() const
{
	return mouseWheel;
}

bool KeyListener::getLeftMouseButton() const
{
	return mouseL;
}

bool KeyListener::getRightMouseButton() const
{
	return mouseR;
}
