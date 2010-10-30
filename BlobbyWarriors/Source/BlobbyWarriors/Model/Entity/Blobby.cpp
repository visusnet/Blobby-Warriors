#include "Blobby.h"

Blobby::Blobby()
{
	this->isOnGround = false;
	this->isJumping = false;
	this->isRotating = false;
	this->isWalking = false;
	this->angle = 0;
	this->direction = DIRECTION_UNKNOWN;

	ContactListener::getInstance()->subscribe(this);
}

void Blobby::step()
{
	// Reposition the weapon.
	if (this->weapon != 0) {
		this->weapon->getBody(0)->SetTransform(this->bodies.at(0)->GetTransform().position, this->weapon->getBody(0)->GetTransform().GetAngle());
	}

	if (this->isJumping && this->isRotating) {		
		// If the blobby is rotating (i.e. doubly jumping), the angle has to
		// be incremented.
		if (this->angle == 360.0f) {
			this->angle = 0.0f;
			this->isJumping = false;
			this->isRotating = false;
		}
		this->angle += 4;
	} else {
		// Otherwise, the angle has to be reset.
		this->angle = 0.0f;
	}

	// Rotate the body.
	b2Body *body = this->bodies.at(0);
	body->SetTransform(body->GetTransform().position, degree2radian(direction == DIRECTION_LEFT ? this->angle : 360 - this->angle));

	if (this->isWalking && this->direction != DIRECTION_UNKNOWN) {
		if (this->direction == DIRECTION_LEFT) {
			body->SetLinearVelocity(b2Vec2(-10.0f, body->GetLinearVelocity().y));
		} else if (this->direction == DIRECTION_RIGHT) {
			body->SetLinearVelocity(b2Vec2(10.0f, body->GetLinearVelocity().y));
		}
	}
}

bool isBlobby(b2Fixture *fix)
{
	return dynamic_cast<Blobby*>((IEntity*)fix->GetBody()->GetUserData()) != 0;
}
bool isGround(b2Fixture *fix)
{
	return dynamic_cast<Ground*>((IEntity*)fix->GetBody()->GetUserData()) != 0;
}

void Blobby::update(Publisher *who, UpdateData *what)
{
	ContactEventArgs *contactEventArgs = dynamic_cast<ContactEventArgs*>(what);
	if (contactEventArgs != 0) {
		b2Body *body = this->bodies.at(0);
		// Did we hit or cease to hit the ground?
		b2Body *contactBody = 0;
		if (contactEventArgs->contact->GetFixtureA()->GetBody() == body) {
			contactBody = contactEventArgs->contact->GetFixtureB()->GetBody();
		} else if (contactEventArgs->contact->GetFixtureB()->GetBody() == body) {
			contactBody = contactEventArgs->contact->GetFixtureA()->GetBody();
		}
/*		for (b2Contact *c = contactEventArgs->contact; c; c = c->GetNext()) {
			if ((c->GetFixtureA()->IsSensor() && isBlobby(c->GetFixtureA()) && isGround(c->GetFixtureB()))
			 || (c->GetFixtureB()->IsSensor() && isBlobby(c->GetFixtureB()) && isGround(c->GetFixtureA()))) {
				 if (c->IsTouching()) {
					debug("hitting ground");
					this->isOnGround = true;
					this->isJumping = false;
					this->isRotating = false;
				 } else {
					debug("leaving ground");
					this->isOnGround = false;
				 }
//				debug("blobby -> ground | %i | cp: %f %f", c->GetFixtureA()->IsSensor(), c->GetManifold()->localPoint.x, c->GetManifold()->localPoint.y);
//				debug("ground -> blobby | %i | cp: %f %f", c->GetFixtureB()->IsSensor(), c->GetManifold()->localPoint.x, c->GetManifold()->localPoint.y);
			}
		}*/
		if (contactBody != 0) {
			Ground *ground = dynamic_cast<Ground*>((IEntity*)contactBody->GetUserData());
			if (ground != 0) {
				// Yes, we did!
				if (contactEventArgs->type == CONTACT_TYPE_BEGIN) {
					debug("hitting ground");
					this->isOnGround = true;
					this->isJumping = false;
					this->isRotating = false;
				} else if (contactEventArgs->type == CONTACT_TYPE_END) {
					debug("leaving ground");
					this->isOnGround = false;
				}
			}
		}
	}
}

void Blobby::draw()
{
	GraphicsEngine::drawString(35, 40, "isOnGround = %s", this->isOnGround ? "true" : "false");
	GraphicsEngine::drawString(35, 55, "inJumping  = %s", this->isJumping ? "true" : "false");
	GraphicsEngine::drawString(35, 70, "isRotating = %s", this->isRotating ? "true" : "false");

	AbstractEntity::draw();
}

void Blobby::setController(IController *controller)
{
	this->controller = controller;
	this->controller->setBlobby(this);
}

void Blobby::addWearable(IWearable *wearable)
{
	this->wearables.push_back(wearable);
}

IWearable* Blobby::getWearable(unsigned int i)
{
	if (0 <= i && i < this->wearables.size()) {
		return this->wearables.at(i);
	}
	return 0;
}

unsigned int Blobby::getWearableCount()
{
	return this->wearables.size();
}

void Blobby::setWeapon(AbstractWeapon *weapon)
{
	this->weapon = weapon;

	// Reposition weapon.
	if (this->weapon != 0) {
		this->weapon->getBody(0)->SetTransform(this->bodies.at(0)->GetTransform().position, this->weapon->getBody(0)->GetTransform().GetAngle());
	}

	// Connect weapon to body.
/*	b2RevoluteJointDef jointDef;
	jointDef.Initialize(this->bodies.at(0), this->weapon->getBody(0), this->bodies.at(0)->GetWorldCenter());
	jointDef.enableMotor = true;
	jointDef.motorSpeed = 1.2f;
	GameWorld::getInstance()->getPhysicsWorld()->CreateJoint(&jointDef);*/
}

AbstractWeapon* Blobby::getWeapon()
{
	return this->weapon;
}

void Blobby::jump()
{
	debug("is on ground? %i", this->isOnGround ? 1 : 0);
	debug("is jumping?   %i", this->isJumping ? 1 : 0);
	b2Body *body = this->bodies.at(0);
	if (!this->isJumping) {
		// The blobby is not jumping yet.
		if (this->isOnGround) {
			// The blobby is on the ground, i.e. jump!
			body->ApplyForce(b2Vec2(0.0f, 440.0f), body->GetPosition());
			this->isJumping = true;
			this->isOnGround = false;
		}
	} else if (!this->isRotating) {
		// Enable rotation on double jump (+ boost).
		body->ApplyForce(b2Vec2(0.0f, 200.0f), body->GetPosition());
		this->isRotating = true;
	}
}

void Blobby::walkLeft()
{
	this->direction = DIRECTION_LEFT;
	this->isWalking = true;
}

void Blobby::walkRight()
{
	this->direction = DIRECTION_RIGHT;
	this->isWalking = true;
}

void Blobby::stopWalk()
{
	if (this->isWalking && this->isOnGround) {
		b2Body *body = this->bodies.at(0);
		body->SetLinearVelocity(b2Vec2(0.0f, body->GetLinearVelocity().y));
		switch (this->direction) {
		case DIRECTION_RIGHT:
			body->ApplyForce(b2Vec2(4.0f, 0.0f), body->GetWorldCenter());
			break;
		case DIRECTION_LEFT:
			body->ApplyForce(b2Vec2(-4.0f, 0.0f), body->GetWorldCenter());
			break;
		}
	}
	this->isWalking = false;
}