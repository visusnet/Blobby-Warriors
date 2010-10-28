#include "PlayerController.h"

PlayerController::PlayerController()
{
	this->isJumping = false;
	this->isRotating = false;
	this->angle = 0;
	this->direction = DIRECTION_UNKNOWN;

	GraphicsEngine::getInstance()->subscribe(this);
	KeyboardHandler::getInstance()->subscribe(this);
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

	// Enable rotation on double jump (+ boost).
	KeyEventArgs *eventArgs = dynamic_cast<KeyEventArgs*>(what);
	if (eventArgs != 0) {
		if (eventArgs->key.code == 'w' && this->isJumping) {
			body->ApplyForce(b2Vec2(0.0f, 100.0f), body->GetPosition());
			this->isRotating = true;
		}
	}

	body->SetTransform(body->GetTransform().position, degree2radian(direction == DIRECTION_LEFT ? this->angle : 360 - this->angle));

	if (body->GetLinearVelocity().y == 0) {
		this->isRotating = false;
	}

	if (KeyboardHandler::getInstance()->isKeyDown('w')) {
		if (body->GetLinearVelocity().y == 0) {
			body->ApplyForce(b2Vec2(0.0f, 240.0f), body->GetPosition());
			this->isJumping = true;
		}
	}

	if (KeyboardHandler::getInstance()->isKeyDown('a')) {
		debug("applying force (a)");
		body->SetLinearVelocity(b2Vec2(-10.0f, body->GetLinearVelocity().y));
		this->direction = DIRECTION_LEFT;
	} else if (KeyboardHandler::getInstance()->isKeyDown('d')) {
		debug("applying force (d)");
		body->SetLinearVelocity(b2Vec2(10.0f, body->GetLinearVelocity().y));
		this->direction = DIRECTION_RIGHT;
	} else {
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
	}
}