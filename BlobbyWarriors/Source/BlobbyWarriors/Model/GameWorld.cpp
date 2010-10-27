#include "GameWorld.h"

GameWorld* GameWorld::getInstance()
{
	static Guard guard;
	if(GameWorld::instance == 0) {
		GameWorld::instance = new GameWorld();
	}
	return GameWorld::instance;
}

b2World* GameWorld::getPhysicsWorld()
{
	return this->world;
}

void GameWorld::step()
{
//	debug("World step");
	this->world->Step(1.0f / 62.5f, 10, 10);
}

GameWorld::GameWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, -9.81f);
	bool doSleep = false;
	this->world = new b2World(gravity, doSleep);
}

GameWorld::~GameWorld()
{
	delete this->world;
}

GameWorld *GameWorld::instance = 0;