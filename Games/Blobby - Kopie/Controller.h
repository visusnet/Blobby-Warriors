#pragma once

#include "Globals.h"
#include "Blobby.h"

class Blobby;

class Controller
{
public:
	Controller();
	~Controller();
	virtual void OnKeyEvent(unsigned int flag, bool state, int duration) = 0;
	void SetBlobby(Blobby *blobby);
protected:
	Blobby *blobby;
};
