#include "PlayerController.h"

PlayerController::PlayerController()
{
	KeyboardHandler::getInstance()->subscribe(this);
}

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
			debug("applying force (w)");
			body->ApplyForce(b2Vec2(0.0f, 400.0f), body->GetPosition());
		}
	} else {
//		body->SetLinearVelocity(b2Vec2(body->GetLinearVelocity().x, 0.0f));
	}
/*	if (KeyboardHandler::getInstance()->isKeyDown('s')) {
	} */
	if (KeyboardHandler::getInstance()->isKeyDown('a')) {
		debug("applying force (a)");
		body->SetLinearVelocity(b2Vec2(-400.0f, body->GetLinearVelocity().y));
	} else {
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
	}
	if (KeyboardHandler::getInstance()->isKeyDown('d')) {
		debug("applying force (d)");
		body->SetLinearVelocity(b2Vec2(400.0f, body->GetLinearVelocity().y));
	} else {
		body->SetLinearVelocity(b2Vec2(0, body->GetLinearVelocity().y));
	}
}

void PlayerController::update(Publisher *who, UpdateData *what)
{
	this->step();
}
