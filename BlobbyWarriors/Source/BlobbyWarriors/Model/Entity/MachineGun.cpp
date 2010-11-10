#include "MachineGun.h"

MachineGun::MachineGun()
{
	this->texture = TextureManager::getInstance()->loadTexture(L"data/images/machinegun/machinegun.bmp", 0, new Color(255, 0, 0));
}

void MachineGun::draw()
{
	Texturizer::draw(this->texture, this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, degree2radian(radian2degree(this->getBody(0)->GetTransform().GetAngle()) + 180), 40, 19);
//	AbstractEntity::draw();
}

void MachineGun::fire(b2Vec2 direction, bool constantFire, bool isPlayer)
{
	direction.Normalize();
	EntityFactory *entityFactory = new MachineGunBulletFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = meter2pixel(this->getBody(0)->GetPosition().x);
	properties.y = meter2pixel(this->getBody(0)->GetPosition().y);
	properties.special = true;
	MachineGunBullet *machineGunBullet = (MachineGunBullet*)entityFactory->create(properties);
	machineGunBullet->getBody(0)->ApplyForce(0.81f * direction, this->getBody(0)->GetPosition());
}