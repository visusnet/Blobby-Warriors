#ifndef MACHINEGUNBULLET_H
#define MACHINEGUNBULLET_H

class MachineGunBullet;

#include "AbstractEntity.h"
#include "..\..\PublishSubscribe.h"
#include "..\..\Debug.h"

class MachineGunBullet : public AbstractEntity, public Subscriber
{
public:
	MachineGunBullet();
	void draw();
	void update(Publisher *who, UpdateData *what = 0);
};

#endif