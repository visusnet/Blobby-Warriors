#ifndef ABSTRACTWEAPON_H
#define ABSTRACTWEAPON_H

class AbstractWeapon;

#include "AbstractEntity.h"
#include "IWearable.h"

class AbstractWeapon : public AbstractEntity, public IWearable
{
public:
	virtual void fire(b2Vec2 direction, bool constantFire, bool isPlayer = false) = 0;
};

#endif