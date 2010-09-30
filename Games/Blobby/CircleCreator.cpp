#include "CircleCreator.h"

Circle* CircleCreator::Create(GameObjectSettings settings)
{
	Circle *circle = new Circle();

	b2CircleDef shapeDef;
	shapeDef.radius = settings.radius;
	shapeDef.density = settings.density;
	shapeDef.friction = settings.friction;
	shapeDef.restitution = settings.restitution;

	b2BodyDef bodyDef;
	bodyDef.position.Set(settings.x, settings.y);
	bodyDef.angle = settings.angle;

	b2Body *body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);

	body->CreateShape(&shapeDef);
	body->SetMassFromShapes();
	body->SetUserData((void*)circle);

	circle->SetBody(body);

	return circle;
}

GameObjectSettings CircleCreator::GetDefaultSettings()
{
	GameObjectSettings settings;
	settings.density = 1.0f;
	settings.friction = 0.2f;
	settings.restitution = 0.0f;
	settings.x = 0.0f / SCALING_FACTOR;
	settings.y = -30.0f / SCALING_FACTOR;
	settings.angle = 0.0f;
	settings.radius = 30 / SCALING_FACTOR;

	return settings;
}

int CircleCreator::GetObjectCount()
{
	int count = 0;
	b2Body *body = World::GetInstance()->GetPhysicsWorld()->GetBodyList();

	while (body)
	{
		if (body->GetUserData() != NULL)
		{
			GameObject *gameObject = (GameObject*)body->GetUserData();
			Circle *castedGameObject = dynamic_cast<Circle*>(gameObject);
			if (castedGameObject != NULL)
			{
				count++;
			}
		}

		body = body->GetNext();
	}

	return count;
}
