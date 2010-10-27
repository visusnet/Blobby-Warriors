#include "Ground.h"

void Ground::setBody(b2Body *body)
{
	this->body = body;
	this->body->SetUserData((void*)this);
}

void Ground::draw()
{
	debug("draw");
}