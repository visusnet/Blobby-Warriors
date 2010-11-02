#include "Blobby.h"

Blobby::Blobby()
{
	this->isJumping = false;
	this->isRotating = false;
	this->isWalking = false;
	this->isDucking = false;
	this->isStandingUp = false;
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
		if (this->angle >= 360.0f) {
			this->angle = 0.0f;
			this->isJumping = false;
			this->isRotating = false;
		}
		// Rotate faster, if the blobby is ducking.
		if (this->isDucking) {
			this->angle += 12;
		} else {
			this->angle += 4;
		}
	} else {
		// Otherwise, the angle has to be reset.
		this->angle = 0.0f;
	}

	// Rotate the body.
	b2Body *body = this->bodies.at(0);
	body->SetTransform(body->GetTransform().position, degree2radian(direction == DIRECTION_LEFT ? this->angle : 360 - this->angle));

	// Check whether the body is touching a wall.
	int wallDirection = DIRECTION_UNKNOWN;
	bool isTouchingWall = this->isTouchingWall(&wallDirection);
	// Move the body if it is not touching a wall or is
	// touching a wall but the movement points into the opposite
	// direction.
	if (this->isWalking && this->direction != DIRECTION_UNKNOWN) {
		if (this->direction == DIRECTION_LEFT && (!isTouchingWall || isTouchingWall && wallDirection != DIRECTION_LEFT)) {
			body->SetLinearVelocity(b2Vec2(-10.0f, body->GetLinearVelocity().y));
		} else if (this->direction == DIRECTION_RIGHT && (!isTouchingWall || isTouchingWall && wallDirection != DIRECTION_RIGHT)) {
			body->SetLinearVelocity(b2Vec2(10.0f, body->GetLinearVelocity().y));
		}
	}

	// Duck and cover. ;-)
	if (this->isDucking || this->isStandingUp) {
		b2CircleShape *shape = (b2CircleShape*)this->bodies.at(0)->GetFixtureList()->GetNext()->GetShape();
		if (this->isDucking) {
			shape->m_p.Set(shape->m_p.x, max(0.1856f, shape->m_p.y - 0.02f));
			if (shape->m_p.y == 0.1856f) {
				this->isDucking = false;
			}
		} else {
			shape->m_p.Set(shape->m_p.x, min(0.3856f, shape->m_p.y + 0.02f));
			if (shape->m_p.y == 0.3856f) {
				this->isStandingUp = false;
			}
		}
	}
}

bool isLeftSensor(b2Fixture *fixture)
{
	bool isSensor = fixture->IsSensor();
	bool isPolygon = fixture->GetShape()->GetType() == b2Shape::e_polygon;

	if (isSensor && isPolygon) {
		b2PolygonShape *polygonShape = (b2PolygonShape*)fixture->GetShape();

		if (polygonShape->m_vertices[0] == b2Vec2(0, 0) && polygonShape->m_vertices[1] == b2Vec2(-0.386f, 0.386f) && polygonShape->m_vertices[2] == b2Vec2(-0.386f, -0.386f)) {
			return true;
		}

		return true;
	}

	return false;
}

void Blobby::update(Publisher *who, UpdateData *what)
{
	ContactEventArgs *contactEventArgs = dynamic_cast<ContactEventArgs*>(what);
	if (contactEventArgs != 0) {
		// Did we hit or cease to hit the ground?
		b2Fixture *blobbyFixture = 0;
		b2Fixture *groundFixture = 0;
		// Sort the fixtures.
		if (contactEventArgs->contact->GetFixtureA()->GetBody() == this->bodies.at(0)) {
			blobbyFixture = contactEventArgs->contact->GetFixtureA();
			groundFixture = contactEventArgs->contact->GetFixtureB();
		} else if (contactEventArgs->contact->GetFixtureB()->GetBody() == this->bodies.at(0)) {
			groundFixture = contactEventArgs->contact->GetFixtureA();
			blobbyFixture = contactEventArgs->contact->GetFixtureB();
		}
		if (groundFixture != 0) {
			// There is a fixture which might be a ground.
			Ground *ground = dynamic_cast<Ground*>((IEntity*)groundFixture->GetBody()->GetUserData());
			if (ground != 0) {
				// Yes, it is really a ground.
				const b2Manifold* manifold = contactEventArgs->contact->GetManifold();
				if (contactEventArgs->type == CONTACT_TYPE_BEGIN && manifold->pointCount != 0) {
					// The contact has begun and there are contact points.

					// Every hit with a ground forces the blobby to stop
					// rotating and jumping.
					this->isRotating = false;
					this->isJumping = false;

					// Calculate the contact point in world coordinates.
					b2PointState state1[b2_maxManifoldPoints], state2[b2_maxManifoldPoints];
					b2GetPointStates(state1, state2, manifold, manifold);
					b2WorldManifold worldManifold;
					contactEventArgs->contact->GetWorldManifold(&worldManifold);

					for (int i = 0; i < manifold->pointCount; ++i)
					{
						b2Vec2 a = blobbyFixture->GetBody()->GetLocalPoint(worldManifold.points[i]);
						b2Vec2 b = b2Vec2(1, 0);
						a.Normalize();
						b.Normalize();
						float angle = acosf(a.x * b.x + a.y * b.y);

						if (a.y > b.y) {
							angle = b2_pi - angle;
						}

						// If the contact point is real, i.e. the shapes are
						// really touching.
						if (contactEventArgs->contact->IsTouching()) {
							// Create a new ContactPoint that represents a contact
							// to a ground with a specific angle which can is used
							// to distinguish between wall and ground.
							ContactPoint *contactPoint = new ContactPoint();
							contactPoint->fixture = groundFixture;
							contactPoint->angle = radian2degree(angle);
							this->contactPoints.push_back(contactPoint);
						}
					}
				} else if (contactEventArgs->type == CONTACT_TYPE_END) {
					// The contact has ended. We need to remove the ContactPoint.
					list<ContactPoint*> destroyableContactPoints;
					for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
						ContactPoint *cp = *it;
						if (cp->fixture == groundFixture) {
							destroyableContactPoints.push_back(cp);
						}
					}
					for (list<ContactPoint*>::iterator it = destroyableContactPoints.begin(); it != destroyableContactPoints.end(); ++it) {
						this->contactPoints.remove(*it);
					}
				}
			}
		}
	}
}

void Blobby::draw()
{
	int wallDirection = 0;
	GraphicsEngine::drawString(35, 40, "isOnGround     = %s", this->isOnGround() ? "true" : "false");
	GraphicsEngine::drawString(35, 55, "inJumping      = %s", this->isJumping ? "true" : "false");
	GraphicsEngine::drawString(35, 70, "isRotating     = %s", this->isRotating ? "true" : "false");
	GraphicsEngine::drawString(35, 85, "isTouchingWall = %s (%s)", this->isTouchingWall(&wallDirection) ? "true" : "false", wallDirection == DIRECTION_LEFT ? "left" : wallDirection == DIRECTION_RIGHT ? "right" : "unknown");

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
}

AbstractWeapon* Blobby::getWeapon()
{
	return this->weapon;
}

void Blobby::jump()
{
	b2Body *body = this->bodies.at(0);
	if (!this->isJumping) {
		// The blobby is not jumping yet.
		if (this->isOnGround()) {
			// The blobby is on the ground, i.e. jump!
			body->ApplyForce(b2Vec2(0.0f, 440.0f), body->GetPosition());
			this->isJumping = true;
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
	if (this->isWalking && this->isOnGround()) {
		// The blobby is walking on ground, so we stop it and apply
		// a low linear force to make it smooth.
		b2Body *body = this->bodies.at(0);
		body->SetLinearVelocity(b2Vec2(0.0f, body->GetLinearVelocity().y));
		switch (this->direction) {
		case DIRECTION_RIGHT:
			debug("stopping smooth");
			body->ApplyForce(b2Vec2(250.0f, 0.0f), body->GetWorldCenter());
			break;
		case DIRECTION_LEFT:
			debug("stopping smooth");
			body->ApplyForce(b2Vec2(-250.0f, 0.0f), body->GetWorldCenter());
			break;
		}
	}
	this->isWalking = false;
}

void Blobby::duck()
{
	this->isDucking = true;
	this->isStandingUp = false;
}

void Blobby::standUp()
{
	this->isDucking = false;
	this->isStandingUp = true;
}

bool Blobby::isOnGround()
{
	// A blobby is on ground if the contact point is in a GROUND_ANGLE
	// wide angle that is equally spanned around the vector pointing
	// from the center of the lower circle shape to its bottom
	// (negative y-axis direction).
	for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
		ContactPoint *contactPoint = *it;
		if (90 - GROUND_ANGLE / 2 <= contactPoint->angle && contactPoint->angle <= 90 + GROUND_ANGLE / 2) {
			return true;
		}
	}
	return false;
}

bool Blobby::isTouchingWall(int *wallDirection)
{
	// A blobby touches a wall if the contact point is outside of a
	// GROUND_ANGLE wide angle that is equally spanned around the
	// vector pointing from the center of the lower circle shape to
	// its bottom (negative y-axis direction).
	for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
		ContactPoint *contactPoint = *it;
		if (contactPoint->angle < 90 - GROUND_ANGLE / 2 || 90 + GROUND_ANGLE / 2 < contactPoint->angle) {
			*wallDirection = contactPoint->angle > 90 + GROUND_ANGLE / 2 && contactPoint->angle < 270 ? DIRECTION_LEFT : DIRECTION_RIGHT;
			return true;
		}
	}
	*wallDirection = DIRECTION_UNKNOWN;
	return false;
}