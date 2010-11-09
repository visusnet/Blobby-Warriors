#ifndef SKATEBOARDFACTORY_H
#define SKATEBOARDFACTORY_H

#include "EntityFactory.h"
#include "../Skateboard.h"

class SkateboardFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif