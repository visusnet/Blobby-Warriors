#include "World.h"

World* World::instance = 0;

World* World::GetInstance()
{
	if (instance == 0)
	{
		instance = new World();
	}

	return instance;
}

World::World()
{
	b2AABB worldAABB;
	worldAABB.lowerBound.Set(-width / SCALING_FACTOR, -height / SCALING_FACTOR);
	worldAABB.upperBound.Set(width / SCALING_FACTOR, height / SCALING_FACTOR);

	b2Vec2 gravity(0.0f, -10.0f);
	bool doSleep = true;

	this->physicsWorld = new b2World(worldAABB, gravity, doSleep);

	b2DebugDraw *debugDraw = new DebugDraw();
	debugDraw->SetFlags(b2DebugDraw::e_shapeBit /*| b2DebugDraw::e_aabbBit | b2DebugDraw::e_centerOfMassBit | b2DebugDraw::e_coreShapeBit | b2DebugDraw::e_obbBit | b2DebugDraw::e_pairBit*/);
	this->physicsWorld->SetDebugDraw(debugDraw);

	/*	b2BodyDef groundBodyDef;
	groundBodyDef.position.Set(0.0f, -10.0f);

	b2Body* groundBody = this->physicsWorld->CreateBody(&groundBodyDef);

	b2PolygonDef groundShapeDef;
	groundShapeDef.SetAsBox(50.0f, 10.0f);
	groundBody->CreateShape(&groundShapeDef);*/
}

World::~World()
{
}

void World::Initialize()
{
	GameObjectCreator *creator = new GroundCreator();
	GameObjectSettings groundSettings = creator->GetDefaultSettings();
	creator->CreateObject(groundSettings);

	groundSettings.vertices.at(0)->Set(-100.0f / SCALING_FACTOR, -5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(1)->Set(100.0f / SCALING_FACTOR, -5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(2)->Set(100.0f / SCALING_FACTOR, 5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(3)->Set(-100.0f / SCALING_FACTOR, 5.0f / SCALING_FACTOR);
	groundSettings.y += 200 / SCALING_FACTOR;

	groundSettings.SetAngleInDegrees(30);
	creator->CreateObject(groundSettings);

	groundSettings.x -= 200 / SCALING_FACTOR;
	groundSettings.y += 200 / SCALING_FACTOR;
	groundSettings.SetAngleInDegrees(-30);
	creator->CreateObject(groundSettings);

	groundSettings.x += 400 / SCALING_FACTOR;
	groundSettings.SetAngleInDegrees(30);
	groundSettings.x += 800 / SCALING_FACTOR;
	creator->CreateObject(groundSettings);

	groundSettings.x -= 200 / SCALING_FACTOR;
	groundSettings.y -= 200 / SCALING_FACTOR;
	groundSettings.SetAngleInDegrees(-30);
	creator->CreateObject(groundSettings);

	groundSettings.angle = -40 * PI / 180;
	groundSettings.x += 80 / SCALING_FACTOR;
	groundSettings.y -= 260 / SCALING_FACTOR;
	creator->CreateObject(groundSettings);

	groundSettings = creator->GetDefaultSettings();
	groundSettings.vertices.at(0)->Set(-400.0f / SCALING_FACTOR, -5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(1)->Set(400.0f / SCALING_FACTOR, -5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(2)->Set(400.0f / SCALING_FACTOR, 5.0f / SCALING_FACTOR);
	groundSettings.vertices.at(3)->Set(-400.0f / SCALING_FACTOR, 5.0f / SCALING_FACTOR);
	groundSettings.x += 500 / SCALING_FACTOR;
	groundSettings.y -= 180 / SCALING_FACTOR;
	groundSettings.angle = 5 * PI / 180;
	creator->CreateObject(groundSettings);

	Player::GetInstance();

	cout << "Initialized..." << endl;
}

void World::Step()
{
	float timeStep = 1.0f / 60.0f;
	int iterations = 10;

	GameObjectCreator *creator = new BoxCreator();
	GameObjectSettings settings = creator->GetDefaultSettings();
	settings.friction = 0.0f;
	if (creator->GetObjectCount() < 100)
	{
		settings.x = (rand() % 1500 + 1 - 750) / SCALING_FACTOR;
		settings.y = (rand() % 300 + 1 + 240) / SCALING_FACTOR;
		creator->CreateObject(settings);
	}
	creator = new CircleCreator();
	settings = creator->GetDefaultSettings();
	settings.restitution = 1.0f;
	settings.x = 300 / SCALING_FACTOR;
	settings.y = -250 / SCALING_FACTOR;
	if (creator->GetObjectCount() < 3)
	{
		settings.restitution = (rand() % 100) / 100.0f;
		settings.radius = (rand() % 50 + 1) / SCALING_FACTOR;
		creator->CreateObject(settings);
	}

	this->physicsWorld->Step(timeStep, iterations);
	this->physicsWorld->Validate();

	b2Body *body = this->physicsWorld->GetBodyList();

	while (body)
	{
		b2Body *currentBody = body;
		body = body->GetNext();

		if (currentBody->IsFrozen())
		{
			if (currentBody == Player::GetInstance()->GetBlobby()->GetBody())
			{
				Player::GetInstance()->Renew();
			}
			else
			{
				this->physicsWorld->DestroyBody(currentBody);
			}
		}
	}
/*		GameObject *gObj = ((GameObject*)body->GetUserData());

		if (gObj != NULL)
		{
			cout << gObj->GetPositionX() << " " << gObj->GetPositionY() << " " << (body->IsStatic() ? "static" : "not static") << endl;
			gObj->Draw();
		}

		body = body->GetNext();
	}*/
}

b2World* World::GetPhysicsWorld()
{
	return this->physicsWorld;
}
