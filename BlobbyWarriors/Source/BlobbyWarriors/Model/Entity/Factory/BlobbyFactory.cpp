#include "BlobbyFactory.h"

IEntity* BlobbyFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(properties.x, properties.y);
	bodyDef.angle = properties.angle;
	bodyDef.fixedRotation = true;
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;

	b2Body *body = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&bodyDef);
	
	b2CircleShape lowerOuterShape;
	lowerOuterShape.m_radius = 0.386f;

	b2FixtureDef lowerOuterFixture;
	lowerOuterFixture.shape = &lowerOuterShape;
	lowerOuterFixture.density = properties.density;
	lowerOuterFixture.friction = properties.friction;
	lowerOuterFixture.restitution = properties.restitution;

	b2CircleShape upperOuterShape;
	upperOuterShape.m_radius = 0.3068f;
	upperOuterShape.m_p.Set(0.0f, 0.3856f);

	b2FixtureDef upperOuterFixture;
	upperOuterFixture.shape = &upperOuterShape;
	upperOuterFixture.density = properties.density;
	upperOuterFixture.friction = properties.friction;
	upperOuterFixture.restitution = properties.restitution;

	body->CreateFixture(&lowerOuterFixture);
	body->CreateFixture(&upperOuterFixture);
	body->ResetMassData();

	Blobby *blobby = new Blobby();
	blobby->setBody(body);

	return blobby;
}

EntityProperties& BlobbyFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 1.0f;
	properties->friction = 0.2f;
	properties->restitution = 0.0f;
	properties->angle = 0;
	properties->radius = -1;
	properties->width = 800;
	properties->height = 10;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}