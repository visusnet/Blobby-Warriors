#include "Simulator.h"

Simulator::Simulator()
{
	KeyboardHandler::getInstance()->subscribe(this);

	this->gameWorld = GameWorld::getInstance();

	EntityFactory *entityFactory = new BlobbyFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = 400;
	properties.y = 400;
	properties.special = true;
	properties.color = new Color(255, 0, 0);
	Blobby *cameraBlobby = static_cast<Blobby*>(entityFactory->create(properties));
	cameraBlobby->setController(new PlayerController());

	properties.special = false;
	properties.x += 150;
	properties.color = new Color(0, 0, 255);
	entityFactory->create(properties);

	entityFactory = new FlamethrowerFactory();
	Flamethrower *flamethrower = (Flamethrower*)entityFactory->create();
	cameraBlobby->addWearable(flamethrower);
	cameraBlobby->setWeapon(flamethrower);
	
	entityFactory = new MachineGunFactory();
	MachineGun *machineGun = (MachineGun*)entityFactory->create();
	cameraBlobby->addWearable(machineGun);

	entityFactory = new BoxFactory();
	properties = entityFactory->getDefaultProperties();
	properties.x = 300;
	properties.y = 500;
	entityFactory->create(properties);


/*	entityFactory = new GraphicFactory();
	GraphicProperties& graphicProperties = (GraphicProperties&)entityFactory->getDefaultProperties();
	graphicProperties.x = 0;
	graphicProperties.y = 0;
	graphicProperties.texture = TextureLoader::createTexture(L"D:/box.jpg");
	entityFactory->create((EntityProperties&)graphicProperties);*/

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

	this->gameWorld->setCameraBlobby(cameraBlobby);

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

	// TODO: Level setup, etc.
//	this->level = new Level();
}

Simulator::~Simulator()
{
	delete this->level;
}

void Simulator::step(float timestep)
{
	this->gameWorld->step(timestep);

	b2Vec2 p = Camera::convertWorldToScreen(meter2pixel(this->gameWorld->getCameraBlobby()->getBody(0)->GetPosition().x), 300.0f);
	if (p.x < 300) {
		Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 - (300 - int(p.x)), 300));
	} else if (p.x > 500) {
		Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 + (int(p.x) - 500), 300));
	}

	Camera::getInstance()->setViewCenter(b2Vec2(meter2pixel(this->gameWorld->getCameraBlobby()->getBody(0)->GetPosition().x), 300.0f));

	//Texturizer::draw(this->texture, pixel2meter(Camera::getInstance()->getViewCenter().x), pixel2meter(300), 0);

	for (unsigned int i = 0; i < this->gameWorld->getEntityCount(); i++) {
		IEntity *entity = this->gameWorld->getEntity(i);
		entity->draw();
	}
}

/*b2Vec2 Simulator::getActorPosition()
{
	return meter2pixel(this->cameraBlobby->getBody(0)->GetPosition());
}*/

void Simulator::update(Publisher *who, UpdateData *what)
{
	KeyEventArgs *keyEventArgs = dynamic_cast<KeyEventArgs*>(what);
	if (keyEventArgs != 0) {
		if (keyEventArgs->key.code == 'b' && keyEventArgs->key.hasChanged && keyEventArgs->key.isPressed) {
			EntityFactory *entityFactory = new BlobbyFactory();
			EntityProperties properties = entityFactory->getDefaultProperties();
			properties.x = float(rand() % 800);
			properties.y = float(400);
			properties.color = new Color(rand() % 255, rand() % 255, rand() % 255);
			entityFactory->create(properties);
		} else if (keyEventArgs->key.code == 'n' && keyEventArgs->key.hasChanged && keyEventArgs->key.isPressed) {
			EntityFactory *entityFactory = new BoxFactory();
			EntityProperties properties = entityFactory->getDefaultProperties();
			properties.x = float(rand() % 800);
			properties.y = float(500);
			entityFactory->create(properties);
		} else if (keyEventArgs->key.code == '1' && keyEventArgs->key.hasChanged && keyEventArgs->key.isPressed) {
			this->gameWorld->getCameraBlobby()->setWeapon((AbstractWeapon*)this->gameWorld->getCameraBlobby()->getWearable(0));
		} else if (keyEventArgs->key.code == '2' && keyEventArgs->key.hasChanged && keyEventArgs->key.isPressed) {
			this->gameWorld->getCameraBlobby()->setWeapon((AbstractWeapon*)this->gameWorld->getCameraBlobby()->getWearable(1));
		}
	}
}
