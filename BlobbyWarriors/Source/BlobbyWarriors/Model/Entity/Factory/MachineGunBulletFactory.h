#ifndef MACHINEGUNBULLETFACTORY_H
#define MACHINEGUNBULLETFACTORY_H

#include "EntityFactory.h"
#include "../MachineGunBullet.h"

class MachineGunBulletFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif