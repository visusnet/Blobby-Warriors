#include "Key.h"

Key::Key(unsigned int flag)
{
	this->flag = flag;
	this->isPressed = false;
	this->previousState = false;
}
		
bool Key::IsPressed()
{
	int now = glutGet(GLUT_ELAPSED_TIME);

	this->duration = now - this->timeDown;
	
	if ((now - this->timeStepDown) > 100 || this->timeDown == 0)
	{
		this->timeStepDown = now;

		return this->isPressed;
	}
	else
	{
		return false;
	}
}
		
bool Key::HasChanged()
{
	bool tmpPreviousState = this->previousState;
	this->previousState = this->isPressed;
	
	if (tmpPreviousState != this->isPressed)
	{
		return true;
	}
	else
	{
		return false;
	}
}
		
void Key::Down()
{
	if (!this->isPressed)
	{
		this->timeDown = glutGet(GLUT_ELAPSED_TIME);
		this->timeStepDown = 0;
		this->duration = 0;
		this->isPressed = true;
	}
}

void Key::Up()
{
	this->timeUp = glutGet(GLUT_ELAPSED_TIME);
	this->isPressed = false;
}

unsigned int Key::GetFlag()
{
	return this->flag;
}
