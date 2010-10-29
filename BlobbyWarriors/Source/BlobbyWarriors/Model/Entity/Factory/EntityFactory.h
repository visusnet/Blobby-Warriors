#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../IEntity.h"
#include "../../GameWorld.h"
#include "../../PhysicsUtils.h"

#define ENTITY_PROPERTY_UNUSED -1.0f

struct EntityProperties
{
	float x;
	float y;
	float width;
	float height;
	float radius;
	float angle;
	float density;
	float friction;
	float restitution;
	bool special;
};

class EntityFactory
{
public:
	IEntity* create();
	virtual IEntity* create(const EntityProperties& properties) = 0;
	virtual EntityProperties& getDefaultProperties() = 0;
};

#endif