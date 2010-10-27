#include "Simulator.h"

Simulator::Simulator()
{
	this->gameWorld = GameWorld::getInstance();

	EntityFactory *entityFactory = new BlobbyFactory();

	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 600;
	this->playerBlobby = static_cast<Blobby*>(entityFactory->create(properties));
	this->playerBlobby->setController(new PlayerController());

	// TODO: Level setup, etc.
	this->level = new Level();
}

Simulator::~Simulator()
{
	delete this->level;
}

void Simulator::step()
{
	this->gameWorld->step();

	this->playerBlobby->draw();
}