#ifndef ABSTRACTCONTROLLER_H
#define ABSTRACTCONTROLLER_H

#include "IController.h"

class AbstractController : public IController
{
public:
	void setBlobby(Blobby *blobby);
	virtual void step();
protected:
	Blobby *blobby;
};

#endif