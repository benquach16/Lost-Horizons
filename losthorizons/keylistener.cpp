#include "stdafx.h"
#include "keylistener.h"

KeyListener::KeyListener()
	: key((EKEY_CODE)0), ch(0), mouseX(0), mouseY(0), mouseWheel(0)
{
	for (unsigned i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		keys[i] = KEY_STATE_UP;
	}
}

bool KeyListener::OnEvent(const SEvent& event)
{
	//get events from operating system
	switch (event.EventType)
	{
	case EET_KEY_INPUT_EVENT:
		if (event.KeyInput.PressedDown) {
			keys[event.KeyInput.Key] = KEY_STATE_PRESSED;
			key = event.KeyInput.Key;
			ch = event.KeyInput.Char;
		} else {
			keys[event.KeyInput.Key] = KEY_STATE_RELEASED;
			key = (EKEY_CODE)0;
			ch = 0;
		}
		break;
	case EET_MOUSE_INPUT_EVENT:
		//mouse events
		switch (event.MouseInput.Event)
		{
		case EMIE_LMOUSE_PRESSED_DOWN:
			keys[KEY_LBUTTON] = KEY_STATE_PRESSED;
			key = KEY_LBUTTON;
			break;
		case EMIE_LMOUSE_LEFT_UP:
			keys[KEY_LBUTTON] = KEY_STATE_RELEASED;
			key = (EKEY_CODE)0;
			break;
		case EMIE_RMOUSE_PRESSED_DOWN:
			keys[KEY_RBUTTON] = KEY_STATE_PRESSED;
			key = KEY_RBUTTON;
			break;
		case EMIE_RMOUSE_LEFT_UP:
			keys[KEY_RBUTTON] = KEY_STATE_RELEASED;
			key = (EKEY_CODE)0;
			break;
		case EMIE_MOUSE_WHEEL:
			// how do i make it work?
			mouseWheel += (int)event.MouseInput.Wheel;
			break;
		default:
			// check the mouse coords
			mouseX = event.MouseInput.X;
			mouseY = event.MouseInput.Y;
			break;
		}
		break;
	}
    return false;
}

const bool KeyListener::isKeyDown(EKEY_CODE keyCode) const
{
	return keys[keyCode] < KEY_STATE_UP;
}

const bool KeyListener::isKeyUp(EKEY_CODE keyCode) const
{
	return keys[keyCode] > KEY_STATE_DOWN;
}

const bool KeyListener::isKeyReleased(EKEY_CODE keyCode)
{
	if (keys[keyCode] == KEY_STATE_RELEASED) {
		keys[keyCode] = KEY_STATE_UP;
		return true;
	}
	return false;
}

const bool KeyListener::isKeyPressed(EKEY_CODE keyCode)
{
	if (keys[keyCode] == KEY_STATE_PRESSED) {
		keys[keyCode] = KEY_STATE_DOWN;
		return true;
	}
	return false;
}

const EKEY_CODE KeyListener::getKey()
{
	EKEY_CODE temp = key;
	key = (EKEY_CODE)0;
	return temp;
}

const char KeyListener::getChar()
{
	unsigned temp = ch;
	ch = 0;
	return temp;
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
