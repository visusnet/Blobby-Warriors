#include "Blobby.h"

Blobby::Blobby(void)
{
	this->controller = NULL;
}

Blobby::~Blobby(void)
{
}

Controller* Blobby::GetController()
{
	return this->controller;
}

void Blobby::SetController(Controller *controller)
{
	this->controller = controller;
	this->controller->SetBlobby(this);
}