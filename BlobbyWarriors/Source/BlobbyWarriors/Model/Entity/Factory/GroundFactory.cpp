#include "GroundFactory.h"

IEntity* GroundFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position = pixel2meter(b2Vec2(properties.x, properties.y));
	bodyDef.angle = radian2degree(properties.angle);
	bodyDef.type = b2BodyType::b2_dynamicBody;

	b2Body *body = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(pixel2meter(properties.width), pixel2meter(properties.height));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = properties.density;
	fixtureDef.friction = properties.friction;
	fixtureDef.restitution = properties.restitution;

	body->CreateFixture(&fixtureDef);
	body->ResetMassData();

	Ground *ground = new Ground();
	ground->setBody(body);

	return ground;
}

EntityProperties& GroundFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 1.0f;
	properties->friction = 0.2f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = //ENTITY_PROPERTY_UNUSED;
	properties->width = 10.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 10.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}