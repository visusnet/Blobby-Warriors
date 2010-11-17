#ifndef BOXFACTORY_H
#define BOXFACTORY_H

#include "EntityFactory.h"
#include "../Box.h"

class BoxFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif