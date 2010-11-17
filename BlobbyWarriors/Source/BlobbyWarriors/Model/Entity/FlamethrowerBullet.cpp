#include "FlamethrowerBullet.h"

FlamethrowerBullet::FlamethrowerBullet()
{
	this->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/machinegun/bullet.png", new Color(255, 0, 0)));
	this->addTexture(TextureManager::getInstance()->loadTexture(L"data/images/light/spot.jpg"));

	this->ticks = glutGet(GLUT_ELAPSED_TIME);

	ContactListener::getInstance()->subscribe(this);
}

void FlamethrowerBullet::step()
{
	if (glutGet(GLUT_ELAPSED_TIME) - this->ticks > FLAMETHROWERBULLET_TTL) {
		ContactListener::getInstance()->unsubscribe(this);
		this->destroy();
	}
}

void FlamethrowerBullet::draw()
{
//	AbstractEntity::draw();
	//Texturizer::draw(this->getTexture(0), this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, this->getBody(0)->GetTransform().GetAngle());

	BlendingInfo *blending = new BlendingInfo();
	blending->sfactor = GL_ONE;
	blending->dfactor = GL_ONE;
	blending->isEnabled = true;
	GLubyte red = 100 + rand() % 155;
	GLubyte green = min(GLubyte(rand() % 255), red);
	Color *color = new Color(red, green, 0);
	Texturizer::draw(this->getTexture(1), this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, 0, 10 + rand() % 10, 10 + rand() % 10, false, blending, color);
	delete blending;
}

void FlamethrowerBullet::update(Publisher *who, UpdateData *what)
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

			Blobby *blobby = dynamic_cast<Blobby*>((IEntity*)contactBody->GetUserData());
			if (blobby != 0) {
				blobby->setHealth(blobby->getHealth() - 2);
			}
		}
	}
}