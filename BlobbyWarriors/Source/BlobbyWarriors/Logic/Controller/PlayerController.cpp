#include "PlayerController.h"

void PlayerController::setBlobby(Blobby *blobby)
{
	this->blobby = blobby;
}

void PlayerController::step()
{
	if (this->blobby == 0) {
		return;
	}

	b2Body *body = this->blobby->getBody();

	if (KeyboardHandler::getInstance()->isKeyDown('w')) {
		if (body->GetLinearVelocity().y == 0) {
			body->ApplyForce(b2Vec2(0.0f, 2.0f), body->GetPosition());
		}
	} else {
		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.0f));
	}
/*	if (KeyboardHandler::getInstance()->isKeyDown('s')) {
	} */
	if (KeyboardHandler::getInstance()->isKeyDown('a')) {
		body->SetLinearVelocity(b2Vec2(-2.0f, body->GetLinearVelocity().y));
	}
	if (KeyboardHandler::getInstance()->isKeyDown('d')) {
		body->SetLinearVelocity(b2Vec2(2.0f, body->GetLinearVelocity().y));
	}
}