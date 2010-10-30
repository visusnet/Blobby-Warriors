#include "Blobby.h"

void Blobby::setController(IController *controller)
{
	this->controller = controller;
	this->controller->setBlobby(this);
}

void Blobby::draw()
{
	if (this->weapon != 0) {
		this->weapon->getBody(0)->SetTransform(this->bodies.at(0)->GetTransform().position, this->weapon->getBody(0)->GetTransform().GetAngle());
	}

	PlayerController *playerController = dynamic_cast<PlayerController*>(this->controller);
	if (playerController != 0) {
		GraphicsEngine::drawString(35, 40, "isOnGround = %s", playerController->getIsOnGround() ? "true" : "false");
		GraphicsEngine::drawString(35, 55, "inJumping  = %s", playerController->getIsJumping() ? "true" : "false");
		GraphicsEngine::drawString(35, 70, "isRotating = %s", playerController->getIsRotating() ? "true" : "false");
	}

	AbstractEntity::draw();
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