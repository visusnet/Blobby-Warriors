#ifndef GAMEWORLD_H
#define GAMEWORLD_H

class GameWorld;

#include <list>

#include <Box2D.h>

#include "../UI/Graphics/GraphicsEngine.h"
#include "Entity/Factory/EntityFactory.h"
#include "Entity/Blobby.h"
#include "../Logic/ContactListener.h"
#include "../Debug.h"

using namespace std;

class GameWorld
{
public:
	static GameWorld* getInstance();

	b2World* getPhysicsWorld();
	void step(float timestep);
	void addEntity(IEntity *entity);
	IEntity* getEntity(unsigned int i);
	unsigned int getEntityCount();
	void destroyEntity(IEntity *entity);
	void setCameraBlobby(Blobby *blobby);
	Blobby* getCameraBlobby();
private:
	GameWorld();
	GameWorld(const GameWorld&);
	~GameWorld();

	static GameWorld *instance;

	b2World *world;
	list<IEntity*> entities;
	list<IEntity*> destroyableEntities;
	Blobby *cameraBlobby;

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