#include "MachineGun.h"

void MachineGun::draw()
{
	AbstractEntity::draw();
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
	machineGunBullet->getBody(0)->ApplyForce(1.81f * direction, this->getBody(0)->GetPosition());
}