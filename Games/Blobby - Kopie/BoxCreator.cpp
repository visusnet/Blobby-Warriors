#include "BoxCreator.h"

Box* BoxCreator::Create(GameObjectSettings settings)
{
	Box *box = new Box();

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
	body->SetUserData((void*)box);

	box->SetBody(body);

	return box;
}

GameObjectSettings BoxCreator::GetDefaultSettings()
{
	GameObjectSettings settings;
	settings.density = 1.0f;
	settings.friction = 0.2f;
	settings.restitution = 0.0f;
	settings.vertices.push_back(new b2Vec2(0.0f / SCALING_FACTOR, 0.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(20.0f / SCALING_FACTOR, 0.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(20.0f / SCALING_FACTOR, 20.0f / SCALING_FACTOR));
	settings.vertices.push_back(new b2Vec2(0.0f / SCALING_FACTOR, 20.0f / SCALING_FACTOR));
	settings.x = 0.0f / SCALING_FACTOR;
	settings.y = -30.0f / SCALING_FACTOR;
	settings.angle = 0.0f;

	return settings;
}

int BoxCreator::GetObjectCount()
{
	int count = 0;
	b2Body *body = World::GetInstance()->GetPhysicsWorld()->GetBodyList();

	while (body)
	{
		if (body->GetUserData() != NULL)
		{
			GameObject *gameObject = (GameObject*)body->GetUserData();
			Box *castedGameObject = dynamic_cast<Box*>(gameObject);
			if (castedGameObject != NULL)
			{
				count++;
			}
		}

		body = body->GetNext();
	}

	return count;
}
