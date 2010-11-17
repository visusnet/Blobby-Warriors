#include "BlobbyFactory.h"

void createTriangleSensor(b2Body *body, b2Vec2 a, b2Vec2 b, b2Vec2 c)
{
	b2PolygonShape polygonShape;
	polygonShape.m_vertexCount = 3;
	polygonShape.m_vertices[0].Set(a.x, a.y);
	polygonShape.m_vertices[1].Set(b.x, b.y);
	polygonShape.m_vertices[2].Set(c.x, c.y);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &polygonShape;
	fixtureDef.isSensor = true;

	body->CreateFixture(&fixtureDef);
}

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
	upperOuterShape.m_radius = BLOBBY_UPPER_RADIUS;
	upperOuterShape.m_p.Set(0.0f, BLOBBY_CENTER_DISTANCE);
//	upperOuterShape.m_radius = 0.3068f;
//	upperOuterShape.m_p.Set(0.0f, 0.3856f);

	b2FixtureDef upperFixtureDef;
	upperFixtureDef.shape = &upperOuterShape;
	upperFixtureDef.density = properties.density;
	upperFixtureDef.friction = properties.friction;
	upperFixtureDef.restitution = properties.restitution;
	if (properties.special) {
		upperFixtureDef.filter.groupIndex = -1;
	}
	upperFixtureDef.filter.categoryBits = COLLISION_BIT_BLOBBY;
	upperFixtureDef.filter.maskBits = COLLISION_BIT_GROUND | COLLISION_BIT_OBJECT | COLLISION_BIT_BULLET | COLLISION_BIT_BLOBBY;	

	b2CircleShape lowerOuterShape;
	lowerOuterShape.m_radius = BLOBBY_LOWER_RADIUS;

	b2FixtureDef lowerFixtureDef;
	lowerFixtureDef.shape = &lowerOuterShape;
	lowerFixtureDef.density = properties.density;
	lowerFixtureDef.friction = properties.friction;
	lowerFixtureDef.restitution = properties.restitution;
	if (properties.special) {
		lowerFixtureDef.filter.groupIndex = -1;
	}
	lowerFixtureDef.filter.categoryBits = COLLISION_BIT_BLOBBY;
	lowerFixtureDef.filter.maskBits = COLLISION_BIT_GROUND | COLLISION_BIT_OBJECT | COLLISION_BIT_BULLET | COLLISION_BIT_BLOBBY;

	body->ResetMassData();

	Blobby *blobby = new Blobby();
	blobby->addBody(body);

	blobby->upperFixture = body->CreateFixture(&upperFixtureDef);
	blobby->lowerFixture = body->CreateFixture(&lowerFixtureDef);

	// Create the blobby textures.
	blobby->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/blobby/blobbym1.bmp", properties.color, new Color(0, 0, 0)));
	blobby->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/blobby/blobbym2.bmp", properties.color, new Color(0, 0, 0)));
	blobby->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/blobby/blobbym3.bmp", properties.color, new Color(0, 0, 0)));
	blobby->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/blobby/blobbym4.bmp", properties.color, new Color(0, 0, 0)));
	blobby->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/blobby/blobbym5.bmp", properties.color, new Color(0, 0, 0)));

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
