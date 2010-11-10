#include "KeyboardHandler.h"

KeyboardHandler* KeyboardHandler::getInstance()
{
	static Guard guard;
	if(KeyboardHandler::instance == 0) {
		KeyboardHandler::instance = new KeyboardHandler();
	}
	return KeyboardHandler::instance;
}

void KeyboardHandler::setKeyDown(unsigned char keyCode)
{
	KeyEventArgs *eventArgs = new KeyEventArgs();
	for (unsigned int i = 0; i < this->keys.size(); i++) {
		// Is the key already there?
		if (this->keys.at(i).code == keyCode) {
			// Was the key already pressed?
			if (this->keys.at(i).isPressed) {
				this->keys.at(i).hasChanged = false;
			} else {
				this->keys.at(i).isPressed = true;
				this->keys.at(i).ticks = glutGet(GLUT_ELAPSED_TIME);
				this->keys.at(i).hasChanged = true;
			}
			eventArgs->key = this->keys.at(i);
			this->notify(eventArgs);
			if (eventArgs != 0) {
				delete eventArgs;
			}
			return;
		}
	}
	// The key was not there, so create it.
	Key key;
	key.code = keyCode;
	key.isPressed = true;
	key.ticks = glutGet(GLUT_ELAPSED_TIME);
	key.hasChanged = true;
	this->keys.push_back(key);

	eventArgs->key = key;
	this->notify(eventArgs);
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

void KeyboardHandler::setKeyUp(unsigned char keyCode)
{
	for (unsigned int i = 0; i < this->keys.size(); i++) {
		// Is the key already there?
		if (this->keys.at(i).code == keyCode) {
			// Was the key pressed before?
			if (this->keys.at(i).isPressed) {
				this->keys.at(i).hasChanged = true;
			} else {
				this->keys.at(i).hasChanged = false;
			}
			this->keys.at(i).isPressed = false;
			this->keys.at(i).ticks = 0;
			this->notify();
			return;
		}
	}
	Key key;
	key.code = keyCode;
	key.isPressed = false;
	key.ticks = 0;
	key.hasChanged = true;
	this->keys.push_back(key);

	this->notify();
}

bool KeyboardHandler::isKeyDown(unsigned char keyCode)
{
	for (unsigned int i = 0; i < this->keys.size(); i++) {
		if (this->keys.at(i).code == keyCode && this->keys.at(i).isPressed) {
			return true;
		}
	}
	return false;
}

int KeyboardHandler::getKeyDownDuration(unsigned char keyCode)
{
	for (unsigned int i = 0; i < this->keys.size(); i++) {
		if (this->keys.at(i).code = keyCode) {
			return glutGet(GLUT_ELAPSED_TIME) - this->keys.at(i).ticks;
		}
	}
	return 0;
}

KeyboardHandler::KeyboardHandler()
{

}

KeyboardHandler::~KeyboardHandler()
{

}

KeyboardHandler* KeyboardHandler::instance = 0;