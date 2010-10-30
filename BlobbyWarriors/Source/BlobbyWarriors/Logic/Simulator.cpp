#include "Simulator.h"

Simulator::Simulator()
{
	this->gameWorld = GameWorld::getInstance();

	EntityFactory *entityFactory = new BlobbyFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 400;
	properties.special = true;
	this->playerBlobby = static_cast<Blobby*>(entityFactory->create(properties));
	this->playerBlobby->setController(new PlayerController());

	entityFactory = new MachineGunFactory();
	MachineGun *machineGun = (MachineGun*)entityFactory->create();
	this->playerBlobby->addWearable(machineGun);
	this->playerBlobby->setWeapon(machineGun);

	entityFactory = new GroundFactory();
	properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 100;
	properties.width = 800;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = 10;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 790;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 590;
	properties.width = 800;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 100;
	properties.width = 800;
	properties.height = 10;
	properties.angle = 30;
	entityFactory->create(properties);

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

	for (unsigned int i = 0; i < this->gameWorld->getEntityCount(); i++) {
		IEntity *entity = this->gameWorld->getEntity(i);
		entity->draw();
	}
}