#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IController.h"
#include "../../Model/Entity/Blobby.h"
#include "../../Graphics/KeyboardHandler.h"

class PlayerController : public IController, public Subscriber
{
public:
	PlayerController();
	void setBlobby(Blobby *blobby);
	void step();
	void update(Publisher *who, UpdateData *what = 0);
private:
	Blobby *blobby;
};

#endif