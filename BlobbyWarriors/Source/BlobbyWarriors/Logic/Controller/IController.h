#ifndef ICONTROLLER_H
#define ICONTROLLER_H

class Blobby;

class IController
{
public:
	virtual void setBlobby(Blobby *blobby) = 0;
	virtual void step() = 0;
};

#endif