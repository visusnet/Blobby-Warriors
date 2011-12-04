#include "MachineGun.h"

MachineGun::MachineGun()
{
	this->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/machinegun/machinegun.bmp", 0, new Color(255, 0, 0)));
	this->setSound(WEAPON_EVENT_FIRE, "data/sound/weapons/machinegun/shoot.ogg");
}

void MachineGun::onFire(b2Vec2 direction, bool constantFire, bool isPlayer)
{
	direction.Normalize();
	EntityFactory *entityFactory = new MachineGunBulletFactory();
	EntityProperties& properties = entityFactory->getDefaultProperties();
	properties.x = meter2pixel(this->getBody(0)->GetPosition().x);
	properties.y = meter2pixel(this->getBody(0)->GetPosition().y);
	properties.special = true;
	MachineGunBullet *machineGunBullet = (MachineGunBullet*)entityFactory->create(properties);
	machineGunBullet->getBody(0)->ApplyForce(10.81f * direction, this->getBody(0)->GetPosition());
}
