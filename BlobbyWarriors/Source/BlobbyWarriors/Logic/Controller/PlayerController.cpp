#include "PlayerController.h"

PlayerController::PlayerController()
{
	this->isOnGround = false;
	this->isJumping = false;
	this->isRotating = false;
	this->angle = 0;
	this->direction = DIRECTION_UNKNOWN;

	GraphicsEngine::getInstance()->subscribe(this);
	KeyboardHandler::getInstance()->subscribe(this);
	MouseHandler::getInstance()->subscribe(this);
	ContactListener::getInstance()->subscribe(this);
}

void PlayerController::setBlobby(Blobby *blobby)
{
	this->blobby = blobby;
}

void PlayerController::step()
{

}

void PlayerController::update(Publisher *who, UpdateData *what)
{
	if (this->blobby == 0) {
		return;
	}

	// If the blobby is rotating (i.e. doubly jumping), the angle has to
	// be incremented.
	if (this->isJumping && this->isRotating) {
		if (this->angle == 360) {
			this->angle = 0;
			this->isJumping = false;
			this->isRotating = false;
		}
		this->angle = this->angle + 4;
	} else {
		this->angle = 0;
	}

	b2Body *body = this->blobby->getBody(0);

	ContactEventArgs *contactEventArgs = dynamic_cast<ContactEventArgs*>(what);
	if (contactEventArgs != 0) {
		// Did we hit or cease to hit the ground?
		b2Body *contactBody = 0;
		if (contactEventArgs->contact->GetFixtureA()->GetBody() == body) {
			contactBody = contactEventArgs->contact->GetFixtureB()->GetBody();
		} else if (contactEventArgs->contact->GetFixtureB()->GetBody() == body) {
			contactBody = contactEventArgs->contact->GetFixtureA()->GetBody();
		}
		if (contactBody != 0) {
			// Yes, we did!
			Ground *ground = dynamic_cast<Ground*>((IEntity*)contactBody->GetUserData());
			if (ground != 0) {
				if (contactEventArgs->type == CONTACT_TYPE_BEGIN) {
					this->isOnGround = true;
					this->isJumping = false;
					this->isRotating = false;
				} else if (contactEventArgs->type == CONTACT_TYPE_END) {
					this->isOnGround = false;
				}
			}
		}
		// We have to return, since it is not allowed
		// to modify physics within a timestep.
		return;
	}
	
	KeyEventArgs *keyEventArgs = dynamic_cast<KeyEventArgs*>(what);
	if (keyEventArgs != 0) {
		if (keyEventArgs->key.code == 'w' && keyEventArgs->key.hasChanged) {
			debug("is on ground? %i", this->isOnGround ? 1 : 0);
			debug("is jumping?   %i", this->isJumping ? 1 : 0);
			if (!this->isJumping) {
				// The blobby is not jumping yet.
				if (this->isOnGround) {
					// The blobby is on the ground, i.e. jump!
					body->ApplyForce(b2Vec2(0.0f, 440.0f), body->GetPosition());
					this->isJumping = true;
					this->isOnGround = false;
				}
			} else {
				// Enable rotation on double jump (+ boost).
				body->ApplyForce(b2Vec2(0.0f, 200.0f), body->GetPosition());
				this->isRotating = true;
			}
		}
	}

	// Rotate the body.
	body->SetTransform(body->GetTransform().position, degree2radian(direction == DIRECTION_LEFT ? this->angle : 360 - this->angle));

	if (body->GetLinearVelocity().y == 0) {
		this->isRotating = false;
	}

	if (KeyboardHandler::getInstance()->isKeyDown('a')) {
		debug("applying force (a)");
		body->SetLinearVelocity(b2Vec2(-10.0f, body->GetLinearVelocity().y));
		this->direction = DIRECTION_LEFT;
	} else if (KeyboardHandler::getInstance()->isKeyDown('d')) {
		debug("applying force (d)");
		body->SetLinearVelocity(b2Vec2(10.0f, body->GetLinearVelocity().y));
		this->direction = DIRECTION_RIGHT;
	} else if (this->isOnGround) {
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
	

	MouseEventArgs *mouseEventArgs = dynamic_cast<MouseEventArgs*>(what);
	b2Vec2 mousePosition;
	bool fire = false;
	if (mouseEventArgs != 0) {
		mousePosition = pixel2meter(b2Vec2(float(mouseEventArgs->x), float(mouseEventArgs->y)));
		if (mouseEventArgs->type == MOUSE_BUTTON_STATE_CHANGED && mouseEventArgs->state == MOUSE_STATE_PRESSED && mouseEventArgs->button == MOUSE_BUTTON_LEFT) {
			fire = true;
		}
	} else {
		mousePosition = pixel2meter(MouseHandler::getInstance()->getPosition());
	}
	if (this->blobby->getWeapon() != 0) {
		AbstractWeapon *weapon = this->blobby->getWeapon();
		b2Vec2 weaponPosition = weapon->getBody(0)->GetPosition();

		b2Vec2 a = mousePosition - weaponPosition;
		b2Vec2 b = b2Vec2(1, 0);
		a.Normalize();
		b.Normalize();
		float angle = acosf(a.x * b.x + a.y * b.y);

		if (weaponPosition.y > mousePosition.y) {
			angle = b2_pi - angle;
		}

		if (fire) {
			weapon->fire(a, false, true);
			debug("SINGLE FIRE!");
		} else if (MouseHandler::getInstance()->isButtonPressed(MOUSE_BUTTON_LEFT)) {
			weapon->fire(a, false, true);
		}

		weapon->getBody(0)->SetTransform(weapon->getBody(0)->GetPosition(), angle);
	}
}