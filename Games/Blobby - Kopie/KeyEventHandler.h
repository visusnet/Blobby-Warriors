#ifndef KEY_EVENT_HANDLER_H
#define KEY_EVENT_HANDLER_H

#include "KeyList.h"

enum
{
	LEFT = 0x0002,
	RIGHT = 0x0004,
	UP = 0x0008,
	DOWN = 0x0010,
	UNSET1 = 0x0020,
	UNSET2 = 0x0040,
};

enum
{
	KEY_PRESSED = 0x0080,
///	KEY_TOGGLED = 0x0001, Unused
	KEY_RELEASED = 0x0020
};

struct KeyDef
{
	unsigned int flag;
	unsigned int state;
};

class KeyEventHandler
{
public:
	KeyEventHandler(KeyList *keyList);
	void Step();
	void SetKeyDownFunction(void (*keyDownFunction)(unsigned int flag));
	void SetKeyUpFunction(void (*keyUpFunction)(unsigned int flag));

private:
	bool IsKeyPressed(int key);
	void Check(int keyIndex, bool isPressed);

	void (*keyDownFunction)(unsigned int flag);
	void (*keyUpFunction)(unsigned int flag);
	struct KeyDef *keys;
};

#endif
