#include "Flamethrower.h"

Flamethrower::Flamethrower()
{
	this->texture = TextureManager::getInstance()->loadTexture(L"data/images/flamethrower/flamethrower.bmp", 0, new Color(255, 0, 0));
}

void Flamethrower::draw()
{
	Texturizer::draw(this->texture, this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, degree2radian(radian2degree(this->getBody(0)->GetTransform().GetAngle()) + 180), 40, 19);
//	AbstractEntity::draw();
}

void Flamethrower::fire(b2Vec2 direction, bool constantFire, bool isPlayer)
{
	direction.Normalize();
	b2Mat22 matrix1 = b2Mat22(degree2radian(float(rand() % 600) / 100.0f));
	b2Mat22 matrix2 = b2Mat22(degree2radian(float(rand() % 600) / 100.0f));
	b2Mat22 matrix3 = b2Mat22(degree2radian(float(rand() % 600 - 300) / 100.0f));
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