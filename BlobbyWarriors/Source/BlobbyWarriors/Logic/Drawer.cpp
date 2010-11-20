#include "Drawer.h"

Drawer* Drawer::getInstance()
{
	static Guard guard;
	if(Drawer::instance == 0) {
		Drawer::instance = new Drawer();
	}
	return Drawer::instance;
}

void Drawer::draw()
{
	GameWorld *gameWorld = GameWorld::getInstance();
	Blobby *cameraBlobby = gameWorld->getCameraBlobby();

	if (cameraBlobby != 0) {
		b2Vec2 p = Camera::convertWorldToScreen(meter2pixel(cameraBlobby->getBody(0)->GetPosition().x), 300.0f);
		if (p.x < 300) {
			Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 - (300 - int(p.x)), 300));
		} else if (p.x > 500) {
			Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 + (int(p.x) - 500), 300));
		}

		Camera::getInstance()->setViewCenter(b2Vec2(meter2pixel(cameraBlobby->getBody(0)->GetPosition().x), 300.0f));
	}

	//Texturizer::draw(this->texture, pixel2meter(Camera::getInstance()->getViewCenter().x), pixel2meter(300), 0);
	Texturizer::draw(this->texture, 0, 0);

	for (unsigned int i = 0; i < gameWorld->getEntityCount(); i++) {
		IEntity *entity = gameWorld->getEntity(i);
		entity->draw();
	}
}

Drawer::Drawer()
{
	//this->texture = TextureLoader::createTexture(L"data/images/background/wall.jpg");
	this->texture = TextureLoader::createTexture(L"data/levels/Diamond Mine/vorne1.jpg");

}

Drawer::~Drawer()
{
}

Drawer* Drawer::instance = 0;