#ifndef BLOBBYFACTORY_H
#define BLOBBYFACTORY_H

#include "EntityFactory.h"
#include "../Blobby.h"

class BlobbyFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif