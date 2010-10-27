#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "IController.h"
#include "../../Model/Entity/Blobby.h"
#include "../../Graphics/KeyboardHandler.h"

class PlayerController : public IController
{
public:
	void setBlobby(Blobby *blobby);
	void step();
private:
	Blobby *blobby;
};

#endif