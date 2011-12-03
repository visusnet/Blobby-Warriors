#include "PlayerController.h"

PlayerController::PlayerController()
{
	GraphicsEngine::getInstance()->subscribe(this);
	KeyboardHandler::getInstance()->subscribe(this);
	MouseHandler::getInstance()->subscribe(this);
}

void PlayerController::update(Publisher *who, UpdateData *what)
{
	if (this->blobby == 0) {
		return;
	}
	
	KeyEventArgs *keyEventArgs = dynamic_cast<KeyEventArgs*>(what);
	if (!this->handleKeyEvent(keyEventArgs)) {
		return;
	}

	MouseEventArgs *mouseEventArgs = dynamic_cast<MouseEventArgs*>(what);
	if (!this->handleMouseEvent(mouseEventArgs)) {
		return;
	}
}

bool PlayerController::handleKeyEvent(KeyEventArgs *keyEventArgs)
{
	b2Body *body = this->blobby->getBody(0);
	if (keyEventArgs != 0) {
		if (keyEventArgs->key.code == 'w' && keyEventArgs->key.hasChanged) {
			this->blobby->jump();
		}
	}

	if (KeyboardHandler::getInstance()->isKeyDown('a')) {
		this->blobby->walkLeft();
	} else if (KeyboardHandler::getInstance()->isKeyDown('d')) {
		this->blobby->walkRight();
	} else {
		this->blobby->stopWalk();
	}

	if (KeyboardHandler::getInstance()->isKeyDown('s')) {
		this->blobby->duck();
	} else {
		this->blobby->standUp();
	}

	return true;
}

bool PlayerController::handleMouseEvent(MouseEventArgs *mouseEventArgs)
{
	b2Vec2 mousePosition;
	bool fire = false;
	bool stopFire = false;
	if (mouseEventArgs != 0) {
		mousePosition = pixel2meter(Camera::convertScreenToWorld(mouseEventArgs->x, mouseEventArgs->y));
		if (mouseEventArgs->type == MOUSE_BUTTON_STATE_CHANGED && mouseEventArgs->state == MOUSE_STATE_PRESSED && mouseEventArgs->button == MOUSE_BUTTON_LEFT) {
			fire = true;
		} else if (mouseEventArgs->type == MOUSE_BUTTON_STATE_CHANGED && mouseEventArgs->state == MOUSE_STATE_RELEASED && mouseEventArgs->button == MOUSE_BUTTON_LEFT) {
			stopFire = true;
		}
	} else {
		b2Vec2 absoluteMousePosition = MouseHandler::getInstance()->getPosition();
		mousePosition = pixel2meter(Camera::convertScreenToWorld(int(absoluteMousePosition.x), int(absoluteMousePosition.y)));
	}

	// set direction in which blobby is looking
	if (mousePosition.x > this->blobby->getBody(0)->GetPosition().x)
		this->blobby->setViewingDirection(DIRECTION_RIGHT);
	else
		this->blobby->setViewingDirection(DIRECTION_LEFT);


	if (this->blobby->getWeapon() != 0) {
		AbstractWeapon *weapon = this->blobby->getWeapon();
		b2Vec2 weaponPosition = weapon->getBody(0)->GetPosition();

		//b2Vec2 a = mousePosition - weaponPosition + b2Vec2(cosf(this->blobby->getBody(0)->GetAngle()), sinf(this->blobby->getBody(0)->GetAngle()));
		b2Vec2 a = mousePosition - weaponPosition;
		//b2Vec2 a = weaponPosition;
		b2Vec2 b = b2Vec2(1, 0);
		a.Normalize();
		b.Normalize();
		float angle = acosf(a.x * b.x + a.y * b.y);

		if (weaponPosition.y > mousePosition.y) {
			angle = b2_pi - angle;
			angle += degree2radian(180);	// provides 0°-360° angle handling
		}

		if (fire)
		{
			weapon->fire(b2Vec2(cosf(angle + this->blobby->getBody(0)->GetAngle()), sinf(angle + this->blobby->getBody(0)->GetAngle())), false, true);
		}
		else if (MouseHandler::getInstance()->isButtonPressed(MOUSE_BUTTON_LEFT))
		{
			weapon->fire(b2Vec2(cosf(angle + this->blobby->getBody(0)->GetAngle()), sinf(angle + this->blobby->getBody(0)->GetAngle())), false, true);
		}
		else if (stopFire)
		{
			weapon->stopFire();
		}

		// adjust weapon-angle to blobby if blobby is rotating
		if(this->blobby->getIsRotating())
		{
			weapon->getBody(0)->SetTransform(weapon->getBody(0)->GetPosition(), this->blobby->getBody(0)->GetAngle() + angle);
		}
		else
		{
			weapon->getBody(0)->SetTransform(weapon->getBody(0)->GetPosition(), angle);
		}
	}
	return true;
}
