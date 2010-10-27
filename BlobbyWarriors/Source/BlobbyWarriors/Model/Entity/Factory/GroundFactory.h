#ifndef GROUNDFACTORY_H
#define GROUNDFACTORY_H

#include "EntityFactory.h"
#include "../Ground.h"

class GroundFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif