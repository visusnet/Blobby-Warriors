#include "Simulator.h"

Simulator::Simulator()
{
	this->gameWorld = GameWorld::getInstance();

	EntityFactory *entityFactory = new BlobbyFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 400;
	properties.special = true;
	this->cameraBlobby = static_cast<Blobby*>(entityFactory->create(properties));
	this->cameraBlobby->setController(new PlayerController());

	entityFactory = new MachineGunFactory();
	MachineGun *machineGun = (MachineGun*)entityFactory->create();
	this->cameraBlobby->addWearable(machineGun);
	this->cameraBlobby->setWeapon(machineGun);

	entityFactory = new GroundFactory();
	properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 100;
	properties.width = 1600;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = -395;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 1195;
	properties.y = 300;
	properties.width = 10;
	properties.height = 600;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 590;
	properties.width = 1600;
	properties.height = 10;
	entityFactory->create(properties);
	properties.x = 400;
	properties.y = 100;
	properties.width = 800;
	properties.height = 10;
	properties.angle = 30;
	entityFactory->create(properties);

	// Skateboard experiment... Something for the future...
/*	entityFactory = new SkateboardFactory();
	properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 220;
	Skateboard *skateboard = (Skateboard*)entityFactory->create(properties);

	b2WeldJointDef jointDef;
	jointDef.Initialize(this->cameraBlobby->getBody(0), skateboard->getBody(0), b2Vec2(0.0f, -0.386f));
	jointDef.collideConnected = false;
	jointDef.localAnchorA.Set(0.0f, -0.386f);
	jointDef.localAnchorB.Set(0.0f, 0.0f);
	GameWorld::getInstance()->getPhysicsWorld()->CreateJoint(&jointDef);*/

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

	b2Vec2 p = Camera::convertWorldToScreen(meter2pixel(this->cameraBlobby->getBody(0)->GetPosition().x), 300.0f);
	if (p.x < 300) {
		Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 - (300 - int(p.x)), 300));
	} else if (p.x > 500) {
		Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 + (int(p.x) - 500), 300));
	}

	//Camera::getInstance()->setViewCenter(b2Vec2(meter2pixel(this->cameraBlobby->getBody(0)->GetPosition().x), 300.0f));

	for (unsigned int i = 0; i < this->gameWorld->getEntityCount(); i++) {
		IEntity *entity = this->gameWorld->getEntity(i);
		entity->draw();
	}
}

b2Vec2 Simulator::getActorPosition()
{
	return meter2pixel(this->cameraBlobby->getBody(0)->GetPosition());
}