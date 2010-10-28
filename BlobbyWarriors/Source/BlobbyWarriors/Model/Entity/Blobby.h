#ifndef BLOBBY_H
#define BLOBBY_H

#include <GL/glut.h>

class Blobby;

#include "AbstractEntity.h"
#include "../../Logic/Controller/IController.h"
#include "../../Debug.h"

class Blobby : public AbstractEntity
{
public:
	void setController(IController *controller);
	void draw();
private:
	IController *controller;
};

#endif