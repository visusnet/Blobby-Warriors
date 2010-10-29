#ifndef MACHINEGUN_H
#define MACHINEGUN_H

#include "AbstractWeapon.h"
#include "Factory\MachineGunBulletFactory.h"
#include "../../Debug.h"

class MachineGun : public AbstractWeapon
{
public:
	void draw();
	void fire(b2Vec2 direction, bool constantFire, bool isPlayer = false);
};

#endif