#include "MachineGunBullet.h"

MachineGunBullet::MachineGunBullet()
{
	this->texture = TextureManager::getInstance()->loadTexture(L"data/images/machinegun/bullet.png");

	ContactListener::getInstance()->subscribe(this);
}

void MachineGunBullet::draw()
{
//	AbstractEntity::draw();
	Texturizer::draw(this->texture, this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, this->getBody(0)->GetTransform().GetAngle());
}

void MachineGunBullet::update(Publisher *who, UpdateData *what)
{
	ContactEventArgs *contactEventArgs = dynamic_cast<ContactEventArgs*>(what);
	if (contactEventArgs != 0 && contactEventArgs->type == CONTACT_TYPE_BEGIN) {
		b2Body *contactBody = 0;
		if (contactEventArgs->contact->GetFixtureA()->GetBody() == this->getBody(0)) {
			contactBody = contactEventArgs->contact->GetFixtureB()->GetBody();
		} else if (contactEventArgs->contact->GetFixtureB()->GetBody() == this->getBody(0)) {
			contactBody = contactEventArgs->contact->GetFixtureA()->GetBody();
		}
		if (contactBody != 0) {
			ContactListener::getInstance()->unsubscribe(this);
			this->destroy();
		}
	}
}