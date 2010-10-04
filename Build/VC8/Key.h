#ifndef KEY_H
#define KEY_H

#include "glui/GL/glui.h"

class Key
{
public:
	Key(unsigned int flag);
	bool IsPressed();
	bool HasChanged();
	void Down();
	void Up();
	unsigned int GetFlag();
	bool isPressed;
	int duration;

private:
	unsigned int flag;
	int timeDown;
	int timeUp;
	int timeStepDown;
	bool previousState;
};

#endif
