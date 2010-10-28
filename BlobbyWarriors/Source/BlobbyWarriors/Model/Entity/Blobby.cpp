#include "Blobby.h"

void Blobby::setController(IController *controller)
{
	this->controller = controller;
	this->controller->setBlobby(this);
}

void Blobby::draw()
{
	AbstractEntity::draw();
}