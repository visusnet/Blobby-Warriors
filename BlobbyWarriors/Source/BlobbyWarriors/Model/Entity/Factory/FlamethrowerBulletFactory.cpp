#include "FlamethrowerBulletFactory.h"

IEntity* FlamethrowerBulletFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef = b2BodyDef();
	bodyDef.position.Set(pixel2meter(properties.x), pixel2meter(properties.y));
	bodyDef.angle = radian2degree(properties.angle);
	bodyDef.type = b2_dynamicBody;
	bodyDef.bullet = true;

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
	fixtureDef.filter.categoryBits = COLLISION_BIT_BULLET;
	fixtureDef.filter.maskBits = COLLISION_BIT_OBJECT | COLLISION_BIT_GROUND | COLLISION_BIT_BLOBBY;

	body->CreateFixture(&fixtureDef);
	body->ResetMassData();

	FlamethrowerBullet *flamethrowerBullet = new FlamethrowerBullet();
	flamethrowerBullet->addBody(body);

	return flamethrowerBullet;
}

EntityProperties& FlamethrowerBulletFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 0.1f;
	properties->friction = 0.0f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = 0.0f;//ENTITY_PROPERTY_UNUSED;
	properties->width = 2.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 2.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}