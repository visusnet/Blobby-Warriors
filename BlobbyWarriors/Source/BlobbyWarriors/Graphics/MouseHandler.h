#ifndef MOUSEHANDLER_H
#define MOUSEHANDLER_H

#include <Box2D.h>

#include "../PublishSubscribe.h"

#define MOUSE_STATE_PRESSED 0
#define MOUSE_STATE_RELEASED 1

#define MOUSE_BUTTON_LEFT 0
#define MOUSE_BUTTON_MIDDLE 1
#define MOUSE_BUTTON_RIGHT 2

#define MOUSE_BUTTON_STATE_CHANGED 1
#define MOUSE_POSITION_CHANGED 2

class MouseEventArgs : public UpdateData
{
public:
	int type;
	int x;
	int y;
	int button;
	int state;
};

class MouseHandler : public Publisher
{
public:
	static MouseHandler* getInstance();
	void onMouseButton(int button, int state, int x, int y);
	void onMouseMove(int x, int y);
	bool isButtonPressed(int button);
	b2Vec2 getPosition();
private:
	MouseHandler();
	MouseHandler(const MouseHandler&);
	~MouseHandler();

	static MouseHandler *instance;

	b2Vec2 position;
	bool buttonStates[3];

	class Guard
	{
	public:
		~Guard()
		{
			if (MouseHandler::instance != 0) {
				delete MouseHandler::instance;
			}
		}
	};
	friend class Guard;
};

#endif