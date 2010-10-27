#ifndef GAMEWORLD_H
#define GAMEWORLD_H

#include <Box2D.h>

#include "Entity\Factory\EntityFactory.h"
#include "..\Debug.h"

class GameWorld;

class GameWorld
{
public:
	static GameWorld* getInstance();

	b2World* getPhysicsWorld();
	void step();
private:
	GameWorld();
	GameWorld(const GameWorld&);
	~GameWorld();

	static GameWorld *instance;

	b2World *world;

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