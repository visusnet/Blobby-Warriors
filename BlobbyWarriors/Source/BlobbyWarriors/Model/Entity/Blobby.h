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
	void setBody(b2Body *body);
	b2Body* getBody();
	void setController(IController *controller);
	void draw();
private:
	b2Body *body;
	IController *controller;
};

#endif