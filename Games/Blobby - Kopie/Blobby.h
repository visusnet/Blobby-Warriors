#pragma once

#include <Box2D.h>

#include "GameObject.h"
#include "Controller.h"

class Controller;

class Blobby :
	public GameObject
{
	friend class BlobbyCreator;
public:
	Blobby(void);
	~Blobby(void);
	Controller* GetController();
	void SetController(Controller *controller);
private:
	Controller *controller;
};
