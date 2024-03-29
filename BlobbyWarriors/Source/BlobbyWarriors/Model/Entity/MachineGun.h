#ifndef MACHINEGUN_H
#define MACHINEGUN_H

class MachineGun;

#include "AbstractWeapon.h"
#include "Factory\MachineGunBulletFactory.h"
#include "../../Debug.h"

class MachineGun : public AbstractWeapon
{
public:
	MachineGun();
	void onFire(b2Vec2 direction, bool constantFire, bool isPlayer = false);
};

#endif