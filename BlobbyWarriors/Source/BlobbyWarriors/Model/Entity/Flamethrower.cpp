#include "Flamethrower.h"

Flamethrower::Flamethrower()
{
	this->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/flamethrower/flamethrower.bmp", 0, new Color(255, 0, 0)));
	this->setSound(WEAPON_EVENT_FIRE, "data/sound/weapons/flamethrower/blast.ogg");
}

void Flamethrower::onFire(b2Vec2 direction, bool constantFire, bool isPlayer)
{
	direction.Normalize();
	b2Rot matrix1 = b2Rot(degree2radian(float(rand() % 600) / 100.0f));
	b2Rot matrix2 = b2Rot(degree2radian(float(rand() % 600) / 100.0f));
	b2Rot matrix3 = b2Rot(degree2radian(float(rand() % 600 - 300) / 100.0f));
	direction = b2Mul(matrix1, direction);
	b2Vec2 direction2 = b2Mul(matrix2, direction);
	b2Vec2 direction3 = b2Mul(matrix3, direction);
	EntityFactory *entityFactory = new FlamethrowerBulletFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = meter2pixel(this->getBody(0)->GetPosition().x);
	properties.y = meter2pixel(this->getBody(0)->GetPosition().y);
	properties.special = true;
	float speed = 0.7f;
	FlamethrowerBullet *flamethrowerBullet = (FlamethrowerBullet*)entityFactory->create(properties);
	flamethrowerBullet->getBody(0)->ApplyForce(speed * 0.75f * direction, this->getBody(0)->GetPosition());
	flamethrowerBullet = (FlamethrowerBullet*)entityFactory->create(properties);
	flamethrowerBullet->getBody(0)->ApplyForce(speed * 0.75f * direction2, this->getBody(0)->GetPosition());
	flamethrowerBullet = (FlamethrowerBullet*)entityFactory->create(properties);
	flamethrowerBullet->getBody(0)->ApplyForce(speed * 0.82f * direction3, this->getBody(0)->GetPosition());
}