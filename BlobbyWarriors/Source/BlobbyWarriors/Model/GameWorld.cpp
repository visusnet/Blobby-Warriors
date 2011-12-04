#include "GameWorld.h"

GameWorld* GameWorld::getInstance()
{
	static Guard guard;
	if (GameWorld::instance == 0) {
		GameWorld::instance = new GameWorld();
	}
	return GameWorld::instance;
}

b2World* GameWorld::getPhysicsWorld()
{
	return this->world;
}

void GameWorld::step(float timestep)
{
	// Kill some old entities first.
	for (list<IEntity*>::iterator it = this->destroyableEntities.begin(); it != this->destroyableEntities.end(); ++it) {
		for (unsigned int i = 0; i < (*it)->getBodyCount(); i++) {
			this->world->DestroyBody((*it)->getBody(i));
		}
		this->entities.remove(*it);
		delete (*it);
	}
	this->destroyableEntities.clear();

	this->world->Step(timestep, 10, 10);

	for (list<IEntity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it) {
		(*it)->step();
	}
}

void GameWorld::addEntity(IEntity *entity)
{
	this->entities.push_back(entity);
}

IEntity* GameWorld::getEntity(unsigned int i)
{
	if (0 <= i && i <= this->entities.size()) {
		unsigned int j = 0;
		for (list<IEntity*>::iterator it = this->entities.begin(); it != this->entities.end(); ++it, ++j) {
			if (i == j) {
				return *it;
			}
		}
	}
	return 0;
}

unsigned int GameWorld::getEntityCount()
{
	return this->entities.size();
}

void GameWorld::destroyEntity(IEntity *entity)
{
	this->destroyableEntities.push_back(entity);
}

void GameWorld::setCameraBlobby(Blobby *cameraBlobby)
{
	this->cameraBlobby = cameraBlobby;
}

Blobby* GameWorld::getCameraBlobby()
{
	return this->cameraBlobby;
}

GameWorld::GameWorld()
{
	b2Vec2 gravity = b2Vec2(0.0f, -9.81f);
	bool doSleep = false;
	this->world = new b2World(gravity);
	this->world->SetAllowSleeping(doSleep);
	this->world->SetContactListener(ContactListener::getInstance());
	this->cameraBlobby = 0;
}

GameWorld::~GameWorld()
{
	delete this->world;
}

GameWorld *GameWorld::instance = 0;