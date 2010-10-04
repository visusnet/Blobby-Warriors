#ifndef CONTACT_LISTENER_H
#define CONTACT_LISTENER_H

#include "Box2D.h"

class Game;

class ContactListener : public b2ContactListener
{
public:
	void Add(const b2ContactPoint* point);
	void Persist(const b2ContactPoint* point);
	void Remove(const b2ContactPoint* point);

	Game* game;
};

const int32 k_maxContactPoints = 2048;

enum ContactState
{
	e_contactAdded,
	e_contactPersisted,
	e_contactRemoved,
};

struct ContactPoint
{
	b2Shape* shape1;
	b2Shape* shape2;
	b2Vec2 normal;
	b2Vec2 position;
	b2Vec2 velocity;
	b2ContactID id;
	ContactState state;
};

#include "Game.h"

#endif
