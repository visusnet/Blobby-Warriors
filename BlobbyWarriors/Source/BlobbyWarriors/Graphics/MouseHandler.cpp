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
	MouseEventArgs *eventArgs = new MouseEventArgs();
	eventArgs->type = MOUSE_BUTTON_STATE_CHANGED;
	eventArgs->button = button;
	eventArgs->state = state;
	eventArgs->x = x;
	eventArgs->y = y;
	this->notify(static_cast<UpdateData*>(eventArgs));
	delete eventArgs;
}

void MouseHandler::onMouseMove(int x, int y)
{
	MouseEventArgs *eventArgs = new MouseEventArgs();
	eventArgs->type = MOUSE_POSITION_CHANGED;
	eventArgs->button = -1;
	eventArgs->state = -1;
	eventArgs->x = x;
	eventArgs->y = y;
	this->notify(static_cast<UpdateData*>(eventArgs));
	delete eventArgs;
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