#ifndef FLAMETHROWER_H
#define FLAMETHROWER_H

class Flamethrower;

#include "AbstractWeapon.h"
#include "Factory\FlamethrowerBulletFactory.h"
#include "../../Debug.h"

class Flamethrower : public AbstractWeapon
{
public:
	Flamethrower();
	void onFire(b2Vec2 direction, bool constantFire, bool isPlayer = false);
};

#endif