#include "GraphicFactory.h"

IEntity* GraphicFactory::create(const EntityProperties& properties)
{
	GraphicProperties& graphicProperties = (GraphicProperties&)properties;
	Graphic *graphic = new Graphic();
	graphic->addTexture(graphicProperties.texture);
	graphic->setX(graphicProperties.x);
	graphic->setY(graphicProperties.y);
	graphic->setWidth(graphicProperties.width);
	graphic->setHeight(graphicProperties.height);
	graphic->setDepth(graphicProperties.depth);

	return graphic;
}

EntityProperties& GraphicFactory::getDefaultProperties()
{
	GraphicProperties *properties = new GraphicProperties();
	properties->density = 1.0f;
	properties->friction = 1.0f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = 0.0f; //ENTITY_PROPERTY_UNUSED;
	properties->width = 10.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 10.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	properties->texture = 0;
	properties->depth = 0;
	return *properties;
}