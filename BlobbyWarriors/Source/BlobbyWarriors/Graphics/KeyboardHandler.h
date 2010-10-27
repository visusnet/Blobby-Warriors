#ifndef KEYBOARDHANDLER_H
#define KEYBOARDHANDLER_H

#include <vector>

#include <GL/glut.h>

using namespace std;

struct Key
{
	unsigned char code;
	bool isPressed;
	int ticks;
	bool hasChanged;
};

class KeyboardHandler
{
public:
	static KeyboardHandler* getInstance();
	void setKeyDown(unsigned char keyCode);
	void setKeyUp(unsigned char keyCode);
	bool isKeyDown(unsigned char keyCode);
	int getKeyDownDuration(unsigned char keyCode);
private:
	KeyboardHandler();
	KeyboardHandler(const KeyboardHandler&);
	~KeyboardHandler();

	static KeyboardHandler *instance;

	vector<Key> keys;

	class Guard
	{
	public:
		~Guard()
		{
			if (KeyboardHandler::instance != 0) {
				delete KeyboardHandler::instance;
			}
		}
	};
	friend class Guard;
};

#endif