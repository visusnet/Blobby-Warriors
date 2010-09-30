#include "Controller.h"

class PlayerController :
	public Controller
{
public:
	void OnKeyEvent(unsigned int flag, bool state, int duration);
};
