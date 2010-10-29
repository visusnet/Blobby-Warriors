#ifndef MACHINEGUNFACTORY_H
#define MACHINEGUNFACTORY_H

#include "EntityFactory.h"
#include "../MachineGun.h"

class MachineGunFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif