#include "stdafx.h"
#include "keylistener.h"

#define REPEATDELAY 50
#define REPEATRATE 1 //currently unused

KeyListener::KeyListener()
	: mouseX(0), mouseY(0), mouseWheel(0)
{
	for (unsigned i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		keys[i] = false;
	}
	for (unsigned i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		keysReleased[i] = false;
	}
	for (unsigned i = 0; i < KEY_KEY_CODES_COUNT; ++i) {
		keysRepeatCount[i] = -1;
	}
}

bool KeyListener::OnEvent(const SEvent& event)
{
	//get events from operating system
    if (event.EventType == EET_KEY_INPUT_EVENT)
	{
		if (event.KeyInput.PressedDown)
		{
			keys[event.KeyInput.Key] = true;
			keysReleased[event.KeyInput.Key] = true;
		}
		else
		{
			keys[event.KeyInput.Key] = false;
			keysRepeatCount[event.KeyInput.Key] = -1;
		}
       // keys[event.KeyInput.Key] = event.KeyInput.PressedDown;
	}
	if (event.EventType == EET_MOUSE_INPUT_EVENT) {
		//mouse events
		if (event.MouseInput.Event == EMIE_LMOUSE_PRESSED_DOWN) {
			keys[KEY_LBUTTON] = true;
			keysReleased[KEY_LBUTTON] = true;
		}
		else if (event.MouseInput.Event == EMIE_LMOUSE_LEFT_UP) {
			keys[KEY_LBUTTON] = false;
			keysRepeatCount[KEY_LBUTTON] = -1;
		}
		if (event.MouseInput.Event == EMIE_RMOUSE_PRESSED_DOWN) {
			keys[KEY_RBUTTON] = true;
			keysReleased[KEY_RBUTTON] = true;
		}
		else if (event.MouseInput.Event == EMIE_RMOUSE_LEFT_UP) {
			keys[KEY_RBUTTON] = false;
			keysRepeatCount[KEY_RBUTTON] = -1;
		}
		if (event.MouseInput.Event == EMIE_MOUSE_MOVED) {
			// check the mouse coords
			mouseX = event.MouseInput.X;
			mouseY = event.MouseInput.Y;
		}
		if (event.MouseInput.Event == EMIE_MOUSE_WHEEL) {
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

bool KeyListener::isKeyReleased(EKEY_CODE keyCode)
{
	if (!keys[keyCode] && keysReleased[keyCode])
	{
		keysReleased[keyCode] = false;
		return true;
	}
	return false;
}

bool KeyListener::isKeyPressed(EKEY_CODE keyCode)
{
	if (keys[keyCode])
		keysRepeatCount[keyCode]++;
	return keysRepeatCount[keyCode] == 0 || keysRepeatCount[keyCode] > REPEATDELAY;
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
	return keys[KEY_LBUTTON];
} //can remove and just use the key functions we have

bool KeyListener::getRightMouseButton() const
{
	return keys[KEY_RBUTTON];
} //can remove and just use the key functions we have
