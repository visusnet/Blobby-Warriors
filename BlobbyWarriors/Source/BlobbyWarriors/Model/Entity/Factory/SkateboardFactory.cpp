#include "SkateboardFactory.h"

b2Body* createTire(float x, float y)
{
	b2BodyDef leftTireBodyDef = b2BodyDef();
	leftTireBodyDef.position.Set(x, y);
	leftTireBodyDef.type = b2_dynamicBody;

	b2Body *leftTireBody = GameWorld::getInstance()->getPhysicsWorld()->CreateBody(&leftTireBodyDef);

	b2CircleShape leftTireShape;
	leftTireShape.m_radius = pixel2meter(5.0f);

	b2FixtureDef leftTireFixture;
	leftTireFixture.shape = &leftTireShape;
	leftTireFixture.density = 1.0f;
	leftTireFixture.friction = 1.0f;
	leftTireFixture.restitution = 0.0f;

	leftTireBody->CreateFixture(&leftTireFixture);

	return leftTireBody;
}

IEntity* SkateboardFactory::create(const EntityProperties& properties)
{
	// Board
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

	// Left tire
	b2Body *leftTireBody = createTire(pixel2meter(properties.x - 20.0f), pixel2meter(properties.y));
	b2Body *rightTireBody = createTire(pixel2meter(properties.x + 20.0f), pixel2meter(properties.y));
	
	b2RevoluteJointDef leftTireJointDef;
	leftTireJointDef.Initialize(leftTireBody, body, b2Vec2(pixel2meter(properties.x - 20.0f), pixel2meter(properties.y)));
	leftTireJointDef.motorSpeed = 0.0f;
	leftTireJointDef.maxMotorTorque = 10.0f;
//	leftTireJointDef.enableMotor = true;
	leftTireJointDef.collideConnected = false;
	b2RevoluteJoint *leftTireJoint = (b2RevoluteJoint*)GameWorld::getInstance()->getPhysicsWorld()->CreateJoint(&leftTireJointDef);

	b2RevoluteJointDef rightTireJointDef;
	rightTireJointDef.Initialize(rightTireBody, body, b2Vec2(pixel2meter(properties.x + 20.0f), pixel2meter(properties.y)));
	rightTireJointDef.motorSpeed = 0.0f;
	rightTireJointDef.maxMotorTorque = 10.0f;
//	rightTireJointDef.enableMotor = true;
	rightTireJointDef.collideConnected = false;
	b2RevoluteJoint *rightTireJoint = (b2RevoluteJoint*)GameWorld::getInstance()->getPhysicsWorld()->CreateJoint(&rightTireJointDef);

	Skateboard *skateboard = new Skateboard();
	skateboard->addBody(body);
	skateboard->addBody(leftTireBody);
	skateboard->addBody(rightTireBody);

	return skateboard;
}

EntityProperties& SkateboardFactory::getDefaultProperties()
{
	EntityProperties *properties = new EntityProperties();
	properties->density = 1.0f;
	properties->friction = 1.0f;
	properties->restitution = 0.0f;
	properties->angle = 0.0f;
	properties->radius = 0.0f; //ENTITY_PROPERTY_UNUSED;
	properties->width = 50.0f; //ENTITY_PROPERTY_UNUSED;
	properties->height = 4.0f; //ENTITY_PROPERTY_UNUSED;
	properties->x = 0;
	properties->y = 0;
	return *properties;
}