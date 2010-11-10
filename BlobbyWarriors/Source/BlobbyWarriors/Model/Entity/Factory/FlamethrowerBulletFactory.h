#ifndef MACHINEGUNBULLETFACTORY_H
#define MACHINEGUNBULLETFACTORY_H

#include "EntityFactory.h"
#include "../FlamethrowerBullet.h"

class FlamethrowerBulletFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif