#include "FlamethrowerFactory.h"

IEntity* FlamethrowerFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position.Set(pixel2meter(properties.x), pixel2meter(properties.y));
	bodyDef.angle = radian2degree(properties.angle);
	bodyDef.type = b2_kinematicBody;

	b2Body *body = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&bodyDef);

	b2PolygonShape polygonShape;
	polygonShape.SetAsBox(pixel2meter(properties.width / 2), pixel2meter(properties.height / 2));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.density = properties.density;
	fixtureDef.friction = properties.friction;
	fixtureDef.restitution = properties.restitution;
	if (properties.special) {
		fixtureDef.filter.groupIndex = -1;
	}
	fixtureDef.filter.categoryBits = COLLISION_BIT_WEAPON;
	fixtureDef.filter.maskBits = COLLISION_BIT_OBJECT;

	body->CreateFixture(&fixtureDef);
	body->ResetMassData();

	Flamethrower *flamethrower = new Flamethrower();
	flamethrower->addBody(body);

	return flamethrower;
}

EntityProperties& FlamethrowerFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 0.1f;
	properties->friction = 0.0f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = 0.0f;//ENTITY_PROPERTY_UNUSED;
	properties->width = 40.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 19.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}