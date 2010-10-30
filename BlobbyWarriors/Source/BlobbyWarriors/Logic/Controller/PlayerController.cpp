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

	return true;
}

bool PlayerController::handleMouseEvent(MouseEventArgs *mouseEventArgs)
{
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
		} else if (MouseHandler::getInstance()->isButtonPressed(MOUSE_BUTTON_LEFT)) {
			weapon->fire(a, false, true);
		}

		weapon->getBody(0)->SetTransform(weapon->getBody(0)->GetPosition(), angle);
	}
	return true;
}
