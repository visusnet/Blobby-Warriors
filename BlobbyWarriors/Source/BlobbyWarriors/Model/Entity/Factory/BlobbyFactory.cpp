#include "BlobbyFactory.h"

IEntity* BlobbyFactory::create(const EntityProperties& properties)
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(pixel2meter(properties.x), pixel2meter(properties.y));
	bodyDef.angle = properties.angle;
	bodyDef.fixedRotation = true;
	bodyDef.bullet = true;
	bodyDef.type = b2_dynamicBody;

	b2Body *body = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&bodyDef);

	b2CircleShape upperOuterShape;
	upperOuterShape.m_radius = 0.3068f;
	upperOuterShape.m_p.Set(0.0f, 0.3856f);

	b2FixtureDef upperOuterFixture;
	upperOuterFixture.shape = &upperOuterShape;
	upperOuterFixture.density = properties.density;
	upperOuterFixture.friction = properties.friction;
	upperOuterFixture.restitution = properties.restitution;
	if (properties.special) {
		upperOuterFixture.filter.groupIndex = -1;
	}
	upperOuterFixture.filter.categoryBits = COLLISION_BIT_BLOBBY;
	upperOuterFixture.filter.maskBits = COLLISION_BIT_GROUND | COLLISION_BIT_OBJECT | COLLISION_BIT_BULLET;	

	b2CircleShape lowerOuterShape;
	lowerOuterShape.m_radius = 0.386f;

	b2FixtureDef lowerOuterFixture;
	lowerOuterFixture.shape = &lowerOuterShape;
	lowerOuterFixture.density = properties.density;
	lowerOuterFixture.friction = properties.friction;
	lowerOuterFixture.restitution = properties.restitution;
	if (properties.special) {
		lowerOuterFixture.filter.groupIndex = -1;
	}
	lowerOuterFixture.filter.categoryBits = COLLISION_BIT_BLOBBY;
	lowerOuterFixture.filter.maskBits = COLLISION_BIT_GROUND | COLLISION_BIT_OBJECT | COLLISION_BIT_BULLET;

	b2PolygonShape lowerInnerShape;
	lowerInnerShape.SetAsEdge(b2Vec2(-0.386f + 0.3f, -0.386f), b2Vec2(0.386f - 0.3f, -0.386f));

	b2FixtureDef lowerInnerFixture;
	lowerInnerFixture.shape = &lowerInnerShape;
	lowerInnerFixture.isSensor = true;

	body->CreateFixture(&lowerOuterFixture);
	body->CreateFixture(&upperOuterFixture);
	body->CreateFixture(&lowerInnerFixture);
	body->ResetMassData();

	Blobby *blobby = new Blobby();
	blobby->addBody(body);

	return blobby;
}

EntityProperties& BlobbyFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 1.0f;
	properties->friction = 1.0f;
	properties->restitution = 0.0f;
	properties->angle = 0;
	properties->radius = -1;
	properties->width = 800;
	properties->height = 10;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}
