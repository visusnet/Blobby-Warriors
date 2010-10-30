#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld;

#include <list>

#include <Box2D.h>

#include "Entity/Factory/EntityFactory.h"
#include "../Logic/ContactListener.h"
#include "../Debug.h"

using namespace std;

class GameWorld
{
public:
	static GameWorld* getInstance();

	b2World* getPhysicsWorld();
	void step();
	void addEntity(IEntity *entity);
	IEntity* getEntity(unsigned int i);
	unsigned int getEntityCount();
	void destroyEntity(IEntity *entity);
private:
	GameWorld();
	GameWorld(const GameWorld&);
	~GameWorld();

	static GameWorld *instance;

	b2World *world;
	list<IEntity*> entities;
	list<IEntity*> destroyableEntities;

	class Guard
	{
	public:
		~Guard()
		{
			if (GameWorld::instance != 0) {
				delete GameWorld::instance;
			}
		}
	};
	friend class Guard;
};

#endif