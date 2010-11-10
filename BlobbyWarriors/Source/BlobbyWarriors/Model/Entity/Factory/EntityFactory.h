#ifndef ENTITYFACTORY_H
#define ENTITYFACTORY_H

#include "../IEntity.h"
#include "../../GameWorld.h"
#include "../../PhysicsUtils.h"
#include "../../../UI/Graphics/Color.h"

#define ENTITY_PROPERTY_UNUSED -1.0f

struct EntityProperties
{
	EntityProperties() :
		x(ENTITY_PROPERTY_UNUSED),
		y(ENTITY_PROPERTY_UNUSED),
		width(ENTITY_PROPERTY_UNUSED),
		height(ENTITY_PROPERTY_UNUSED),
		radius(ENTITY_PROPERTY_UNUSED),
		angle(ENTITY_PROPERTY_UNUSED),
		density(ENTITY_PROPERTY_UNUSED),
		friction(ENTITY_PROPERTY_UNUSED),
		restitution(ENTITY_PROPERTY_UNUSED),
		color(0),
		special(false) {}
	float x;
	float y;
	float width;
	float height;
	float radius;
	float angle;
	float density;
	float friction;
	float restitution;
	Color *color;
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