#include "KeyEventHandler.h"

#include "Game.h"

KeyEventHandler::KeyEventHandler(KeyList *keyList)
{
	int length = keyList->Size();

	this->keys = (struct KeyDef*) malloc(length * sizeof(struct KeyDef));

	for (int i = 0; i < length; i++)
	{
		this->keys[i].flag = keyList->GetKeyById(i)->GetFlag();
		this->keys[i].state = 0;
		this->keys[i].state |= KEY_RELEASED;
	}
}

void KeyEventHandler::SetKeyDownFunction(void (*keyDownFunction)(unsigned int flag))
{
	this->keyDownFunction = keyDownFunction;
}

void KeyEventHandler::SetKeyUpFunction(void (*keyUpFunction)(unsigned int flag))
{
	this->keyUpFunction = keyUpFunction;
}

void KeyEventHandler::Step()
{
	this->Check(0, this->IsKeyPressed('A'));
	this->Check(1, this->IsKeyPressed('D'));
	this->Check(2, this->IsKeyPressed('W'));
	this->Check(3, this->IsKeyPressed('S'));
}

bool KeyEventHandler::IsKeyPressed(int key)
{
	if (abs((GetKeyState(key)) & KEY_PRESSED) == KEY_PRESSED)
	{
		return true;
	}

	return false;
}

void KeyEventHandler::Check(int keyIndex, bool isPressed)
{
	/**
	 * Key is pressed and was not pressed before.
	 */
	if (isPressed && (this->keys[keyIndex].state & KEY_RELEASED) == KEY_RELEASED)
	{
		this->keys[keyIndex].state |= KEY_PRESSED;

		this->keyDownFunction(this->keys[keyIndex].flag);
	}
	/**
	 * Key is pressed and was pressed before.
	 */
	else if (isPressed && (this->keys[keyIndex].state & KEY_PRESSED) == KEY_PRESSED)
	{
		this->keyDownFunction(this->keys[keyIndex].flag);
	}
	/**
	 * Key has been released.
	 */
	else if (!isPressed && (this->keys[keyIndex].state & KEY_PRESSED) == KEY_PRESSED)
	{
		this->keys[keyIndex].state |= KEY_RELEASED;

		this->keyUpFunction(this->keys[keyIndex].flag);
	}
	/**
	 * Key was neither pressed nor released.
	 */
	else
	{
		// Nothing to do.
	}
}
