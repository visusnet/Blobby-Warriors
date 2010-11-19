#ifndef GRAPHICFACTORY_H
#define GRAPHICFACTORY_H

#include "EntityFactory.h"
#include "../Graphic.h"

struct GraphicProperties : public EntityProperties
{
	Texture *texture;
	float depth;
};

class GraphicFactory : public EntityFactory
{
public:
	IEntity* create(const EntityProperties& properties);
	EntityProperties& getDefaultProperties();
};

#endif