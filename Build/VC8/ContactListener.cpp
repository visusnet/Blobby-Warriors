#include "ContactListener.h"

#include "RigidBody.h"

void ContactListener::Add(const b2ContactPoint* point)
{
	if (game->m_pointCount == k_maxContactPoints)
	{
		return;
	}

	ContactPoint* cp = game->m_points + game->m_pointCount;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactAdded;

	++game->m_pointCount;
}

void ContactListener::Persist(const b2ContactPoint* point)
{
	RigidBody *rigidBody1 = (RigidBody*)point->shape1->GetBody()->GetUserData();
	RigidBody *rigidBody2 = (RigidBody*)point->shape2->GetBody()->GetUserData();
	Blobby *blobby = NULL;

	if (rigidBody1 != NULL && rigidBody1->type == BLOBBY)
	{
		blobby = (Blobby*) rigidBody1;
	}
	else if (rigidBody2 != NULL && rigidBody2->type == BLOBBY)
	{
		blobby = (Blobby*) rigidBody2;
	}

	if (blobby != NULL && blobby->isJumping)
	{
		blobby->isOnGround = true;
		blobby->isJumping = false;
		blobby->jumpLevel = 0;
	}

	if (game->m_pointCount == k_maxContactPoints)
	{
		return;
	}

	ContactPoint* cp = game->m_points + game->m_pointCount;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactPersisted;

	++game->m_pointCount;
}

void ContactListener::Remove(const b2ContactPoint* point)
{
	if (game->m_pointCount == k_maxContactPoints)
	{
		return;
	}

	ContactPoint* cp = game->m_points + game->m_pointCount;
	cp->shape1 = point->shape1;
	cp->shape2 = point->shape2;
	cp->position = point->position;
	cp->normal = point->normal;
	cp->id = point->id;
	cp->state = e_contactRemoved;

	++game->m_pointCount;
}
