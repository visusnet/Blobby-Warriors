#ifndef FLAMETHROWERBULLET_H
#define FLAMETHROWERBULLET_H

class FlamethrowerBullet;

#include "AbstractEntity.h"
#include "Blobby.h"
#include "..\..\PublishSubscribe.h"
#include "..\..\Debug.h"

#define FLAMETHROWERBULLET_TTL 600

class FlamethrowerBullet : public AbstractEntity, public Subscriber
{
public:
	FlamethrowerBullet();
	void step();
	void draw();
	void update(Publisher *who, UpdateData *what = 0);
private:
	int ticks;
};

#endif