#include "MouseHandler.h"

MouseHandler* MouseHandler::getInstance()
{
	static Guard guard;
	if(MouseHandler::instance == 0) {
		MouseHandler::instance = new MouseHandler();
	}
	return MouseHandler::instance;
}

void MouseHandler::onMouseButton(int button, int state, int x, int y)
{
	this->buttonStates[button] = state == 0;
	MouseEventArgs *eventArgs = new MouseEventArgs();
	eventArgs->type = MOUSE_BUTTON_STATE_CHANGED;
	eventArgs->button = button;
	eventArgs->state = state;
	eventArgs->x = x;
	eventArgs->y = y;
	this->notify(static_cast<UpdateData*>(eventArgs));
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

void MouseHandler::onMouseMove(int x, int y)
{
	this->position.Set(float(x), float(y));
	MouseEventArgs *eventArgs = new MouseEventArgs();
	eventArgs->type = MOUSE_POSITION_CHANGED;
	eventArgs->button = -1;
	eventArgs->state = -1;
	eventArgs->x = x;
	eventArgs->y = y;
	this->notify(static_cast<UpdateData*>(eventArgs));
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

bool MouseHandler::isButtonPressed(int button)
{
	return this->buttonStates[button];
}

b2Vec2 MouseHandler::getPosition()
{
	return this->position;
}

MouseHandler::MouseHandler()
{
	this->position = b2Vec2(0.0f, 0.0f);
	this->buttonStates[MOUSE_BUTTON_LEFT] = false;
	this->buttonStates[MOUSE_BUTTON_MIDDLE] = false;
	this->buttonStates[MOUSE_BUTTON_RIGHT] = false;
}

MouseHandler::~MouseHandler()
{

}

MouseHandler* MouseHandler::instance = 0;