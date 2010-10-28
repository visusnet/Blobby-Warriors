#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IController.h"
#include "../../Model/Entity/Blobby.h"
#include "../../Graphics/GraphicsEngine.h"
#include "../../Graphics/KeyboardHandler.h"

#define DIRECTION_UNKNOWN 0
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2

class PlayerController : public IController, public Subscriber
{
public:
	PlayerController();
	void setBlobby(Blobby *blobby);
	void step();
	void update(Publisher *who, UpdateData *what = 0);
private:
	Blobby *blobby;
	bool isJumping;
	bool isRotating;
	float angle;
	int direction;
};

#endif