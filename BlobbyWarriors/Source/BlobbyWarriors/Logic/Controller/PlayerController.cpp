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
		} else if (MouseHandler::getInstance()->isButtonPressed(MOUSE_BUTTON_LEFT)) {
			weapon->fire(a, false, true);
		} else if (stopFire) {
			weapon->stopFire();
		}

		weapon->getBody(0)->SetTransform(weapon->getBody(0)->GetPosition(), angle);
	}
	return true;
}
