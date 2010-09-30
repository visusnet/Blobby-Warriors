#include "GroundCreator.h"

Ground* GroundCreator::Create(GameObjectSettings settings)
{
	Ground *ground = new Ground();

	b2PolygonDef shapeDef;
	shapeDef.vertexCount = (int)settings.vertices.size();
	for (int i = 0; i < shapeDef.vertexCount; i++)
	{
		shapeDef.vertices[i].Set(settings.vertices.at(i)->x, settings.vertices.at(i)->y);
	}
	shapeDef.density = settings.density;
	shapeDef.friction = settings.friction;
	shapeDef.restitution = settings.restitution;

	b2BodyDef bodyDef;
	bodyDef.position.Set(settings.x, settings.y);
	bodyDef.angle = settings.angle;

	b2Body *body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);

	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();
	body->SetUserData((void*)ground);

	ground->SetBody(body);

	return ground;
}

GameObjectSettings GroundCreator::GetDefaultSettings()
{
	GameObjectSettings settings;
	settings.density = 0.0f;
	settings.friction = 0.5f;
	settings.restitution = 0.3f;
	settings.vertices.push_back(new b2Vec2(0.0f / SCALING_FACTOR, 0.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(800.0f / SCALING_FACTOR, 0.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(800.0f / SCALING_FACTOR, 10.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(0.0f / SCALING_FACTOR, 10.0f / SCALING_FACTOR));
	settings.x = -400.0f / SCALING_FACTOR;
	settings.y = -240.0f / SCALING_FACTOR;
	settings.angle = 0.0f;

	return settings;
}

int GroundCreator::GetObjectCount()
{
	int count = 0;
	b2Body *body = World::GetInstance()->GetPhysicsWorld()->GetBodyList();

	while (body)
	{
		if (body->GetUserData() != NULL)
		{
			GameObject *gameObject = (GameObject*)body->GetUserData();
			Ground *castedGameObject = dynamic_cast<Ground*>(gameObject);
			if (castedGameObject != NULL)
			{
				count++;
			}
		}

		body = body->GetNext();
	}

	return count;
}