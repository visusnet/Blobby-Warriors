#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <vector>

#include <Box2D.h>

#include "Entity\Factory\EntityFactory.h"
#include "..\Debug.h"

using namespace std;

class GameWorld;

class GameWorld
{
public:
	static GameWorld* getInstance();

	b2World* getPhysicsWorld();
	void step();
	void addEntity(IEntity *entity);
	IEntity* getEntity(unsigned int i);
	unsigned int getEntityCount();
private:
	GameWorld();
	GameWorld(const GameWorld&);
	~GameWorld();

	static GameWorld *instance;

	b2World *world;
	vector<IEntity*> entities;

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