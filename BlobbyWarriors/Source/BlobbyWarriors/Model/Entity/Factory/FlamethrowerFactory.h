#ifndef FLAMETHROWERFACTORY_H
#define FLAMETHROWERFACTORY_H

#include "EntityFactory.h"
#include "../Flamethrower.h"

class FlamethrowerFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif