#include "BlobbyCreator.h"

Blobby* BlobbyCreator::Create(GameObjectSettings settings)
{
	Blobby *blobby = new Blobby();

	b2CircleDef lowerOuterShapeDef;
	lowerOuterShapeDef.radius = 0.386f;
	lowerOuterShapeDef.density = settings.density;
	lowerOuterShapeDef.friction = settings.friction;
	lowerOuterShapeDef.restitution = settings.restitution;

	b2CircleDef upperOuterShapeDef;
	upperOuterShapeDef.radius = 0.3068f;
	upperOuterShapeDef.density = settings.density;
	upperOuterShapeDef.friction = settings.friction;
	upperOuterShapeDef.restitution = settings.restitution;
	upperOuterShapeDef.localPosition.Set(0, 0.3856f);

	b2BodyDef bodyDef;
	bodyDef.position.Set(settings.x, settings.y);
	bodyDef.angle = settings.angle;
	bodyDef.fixedRotation = true;

	b2Body *body = World::GetInstance()->GetPhysicsWorld()->CreateBody(&bodyDef);

	body->CreateShape(&lowerOuterShapeDef);
	body->CreateShape(&upperOuterShapeDef);
	body->SetMassFromShapes();
	body->SetUserData((void*)blobby);

	blobby->SetBody(body);

	return blobby;
}

GameObjectSettings BlobbyCreator::GetDefaultSettings()
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

int BlobbyCreator::GetObjectCount()
{
	int count = 0;
	b2Body *body = World::GetInstance()->GetPhysicsWorld()->GetBodyList();

	while (body)
	{
		if (body->GetUserData() != NULL)
		{
			GameObject *gameObject = (GameObject*)body->GetUserData();
			Blobby *castedGameObject = dynamic_cast<Blobby*>(gameObject);
			if (castedGameObject != NULL)
			{
				count++;
			}
		}

		body = body->GetNext();
	}

	return count;
}
