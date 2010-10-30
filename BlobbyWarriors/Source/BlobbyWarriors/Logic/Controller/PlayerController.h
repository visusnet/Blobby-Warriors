#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IController.h"
#include "../ContactListener.h"
#include "../../Model/Entity/Blobby.h"
#include "../../Model/Entity/Ground.h"
#include "../../Graphics/GraphicsEngine.h"
#include "../../Graphics/KeyboardHandler.h"
#include "../../Graphics/MouseHandler.h"

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
	bool handleKeyEvent(KeyEventArgs *keyEventArgs);
	bool handleMouseEvent(MouseEventArgs *mouseEventArgs);
	bool handleContactEvent(ContactEventArgs *contactEventArgs);
	bool getIsOnGround() { return this->isOnGround; }
	bool getIsJumping() { return this->isJumping; }
	bool getIsRotating() { return this->isRotating; }
private:
	Blobby *blobby;
	bool isOnGround;
	bool isJumping;
	bool isRotating;
	float angle;
	int direction;
};

#endif