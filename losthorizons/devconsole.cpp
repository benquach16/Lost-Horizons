#include "stdafx.h"
#include "devconsole.h"
#include "globals.h"
#include <conio.h>

using namespace base;

DevConsole::DevConsole()
	: size(0), index(0)
{
	hstdout = GetStdHandle(STD_OUTPUT_HANDLE);
}

DevConsole::~DevConsole()
{

}

void DevConsole::run()
{
	if (!messages.empty()) {
		//messages.front().run();
		messages.pop();
	}
}

void DevConsole::postMessage()
{
	CONSOLE_SCREEN_BUFFER_INFO csbi;
	GetConsoleScreenBufferInfo(hstdout, &csbi);
	_putch('\n');
	index = size;
	buf[size] = '\0';
	_cputs(buf);

	int keyPressed;
	do {
		keyPressed = _getch();
		switch (keyPressed) {
		case KB_RETURN:
			// parse function here
			SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
			csbi.dwCursorPosition.Y++;
			buf[size] = '\0';
			_putch('>');
			_cputs(buf);
			_putch('\n');
			for (unsigned i = 0; i < size; ++i) {
				_putch(' ');
			}
			_putch('\n');
			index = size = 0;
			break;
		case KB_GRAVEACCENT:
			if (size > 0) {
				COORD old = csbi.dwCursorPosition;
				GetConsoleScreenBufferInfo(hstdout, &csbi);
				csbi.dwCursorPosition.X = 0;
				SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
				for (unsigned i = 0; i < size; ++i) {
					_putch(' ');
				}
				csbi.dwCursorPosition = old;
			}
			SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
			break;
		case KB_BACKSPACE:
			if (index > 0) {
				index--;
				size--;
				_putch('\b');
				if (index == size) {
					_cputs(" \b");
				} else {
					COORD old = csbi.dwCursorPosition;
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					for (unsigned i = index; i < size; ++i) {
						buf[i] = buf[i + 1];
						_putch(buf[i]);
					}
					_putch(' ');
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
					csbi.dwCursorPosition = old;
				}
			}
			break;
		case KB_SPECIAL1:
			break;
		case KB_SPECIAL2:
			switch (_getch()) {
			case KB_UP:
				// use history
				break;
			case KB_LEFT:
				if (index > 0) {
					_putch('\b');
					index--;
				}
				break;
			case KB_RIGHT:
				if (index < size) {
					_putch(buf[index]);
					index++;
				}
				break;
			case KB_DOWN:
				// use history
				break;
			}
			break;
		default:
			if (size < CONSOLEBUFFERSIZE - 1 && __isascii(keyPressed)) {
				_putch(keyPressed);
				if (index < size) {
					COORD old = csbi.dwCursorPosition;
					GetConsoleScreenBufferInfo(hstdout, &csbi);
					for (unsigned i = size; i > index; --i) {
						buf[i] = buf[i - 1];
					}
					for (unsigned i = index + 1; i < size + 1; ++i) {
						_putch(buf[i]);
					}
					SetConsoleCursorPosition(hstdout, csbi.dwCursorPosition);
					csbi.dwCursorPosition = old;
				}
				buf[index] = keyPressed;
				index++;
				size++;
			}
			break;
		}
	} while (keyPressed != KB_GRAVEACCENT);
}
