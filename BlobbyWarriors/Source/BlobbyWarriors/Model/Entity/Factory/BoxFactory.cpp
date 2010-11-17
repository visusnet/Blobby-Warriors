#include "BoxFactory.h"

IEntity* BoxFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position.Set(pixel2meter(properties.x), pixel2meter(properties.y));
	bodyDef.angle = radian2degree(properties.angle);
	bodyDef.type = b2_dynamicBody;

	b2Body *body = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(pixel2meter(properties.width / 2), pixel2meter(properties.height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = properties.density;
	fixtureDef.friction = properties.friction;
	fixtureDef.restitution = properties.restitution;
	fixtureDef.filter.categoryBits = COLLISION_BIT_OBJECT;
	fixtureDef.filter.maskBits = COLLISION_BIT_BLOBBY | COLLISION_BIT_WEAPON | COLLISION_BIT_GROUND | COLLISION_BIT_OBJECT | COLLISION_BIT_BULLET;

	body->CreateFixture(&fixtureDef);
	body->ResetMassData();

	Box *box = new Box();
	box->addBody(body);

	return box;
}

EntityProperties& BoxFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 1.0f;
	properties->friction = 1.0f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = 0.0f; //ENTITY_PROPERTY_UNUSED;
	properties->width = 40.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 40.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}