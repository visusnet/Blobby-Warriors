#include "Blobby.h"

Blobby::Blobby()
{
	this->weapon = 0;
	this->nextWeapon = 0;
	this->isJumping = false;
	this->isRotating = false;
	this->isWalking = false;
	this->isDucking = false;
	this->isStandingUp = false;
	this->isOnGround = false;
	this->isTouchingWall = false;
	this->angle = 0;
	this->movementDirection = DIRECTION_UNKNOWN;
	this->rotationDirection = DIRECTION_UNKNOWN;
	this->wallDirection = DIRECTION_UNKNOWN;
	this->health = BLOBBY_DEFAULT_INITIAL_HEALTH;
	this->maxHealth = BLOBBY_DEFAULT_MAX_HEALTH;
	this->isDead = false;
	this->activeTexture = 0;
	this->opacity = 255;
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);
	this->controller = 0;

	ContactListener::getInstance()->subscribe(this);
}

/**
* get attribute isDucking
* 
* @return bool
*/
bool Blobby::getIsDucking()
{
	return this->isDucking;
}

// Magic. Do not touch.
void Blobby::step()
{
	if (!this->isDead && this->health <= 0) {
		this->health = 0;
		ContactListener::getInstance()->unsubscribe(this);
		this->getBody(0)->SetFixedRotation(false);
		this->isDead = true;
		this->activeTexture = 0;
		//this->destroy();
		return;
	}
	if (this->isDead) {
		if (this->health <= -this->getMaxHealth()) {
			this->destroy();
		}
		if (this->opacity > 70) {
			this->opacity--;
		}
	}

	if (this->controller == 0) {
		return;
	}

	this->isOnGround = this->checkIsOnGround();
	this->isTouchingWall = this->checkIsTouchingWall(&this->wallDirection);

	if (this->nextWeapon != 0) {
		if (this->weapon != 0) {
			this->weapon->setActive(false);
		}
		this->weapon = this->nextWeapon;
		this->weapon->setActive(true);
		this->nextWeapon = 0;
	}

	// Reposition the weapon.
	if (this->weapon != 0)
	{
		if (this->isDucking)
		{
			this->weapon->getBody(0)->SetTransform(this->bodies.at(0)->GetPosition() - b2Vec2(0, 0.2f), this->weapon->getBody(0)->GetAngle());
		}
		else
		{
			this->weapon->getBody(0)->SetTransform(this->bodies.at(0)->GetPosition() - b2Vec2(0, 0.1f), this->weapon->getBody(0)->GetAngle());
		}
	}

	// set viewDirection of weapon
	this->weapon->setViewingDirection(this->getViewingDirection());

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
	body->SetTransform(body->GetPosition(), degree2radian(rotationDirection == DIRECTION_LEFT ? this->angle : 360 - this->angle));

	// Move the body if it is not touching a wall or is
	// touching a wall but the movement points into the opposite
	// direction.
	if (this->isWalking && this->movementDirection != DIRECTION_UNKNOWN) {
		if (this->movementDirection == DIRECTION_LEFT && (!this->isTouchingWall || this->isTouchingWall && this->wallDirection != DIRECTION_LEFT)) {
			if (this->isOnGround) {
				body->SetLinearVelocity(b2Vec2(-BLOBBY_MOVE_VELOCITY, body->GetLinearVelocity().y));
			} else {
				body->ApplyForce(b2Vec2(-BLOBBY_MOVE_VELOCITY, 0), body->GetPosition());
			}
		} else if (this->movementDirection == DIRECTION_RIGHT && (!this->isTouchingWall || this->isTouchingWall && this->wallDirection != DIRECTION_RIGHT)) {
			if (this->isOnGround) {
				body->SetLinearVelocity(b2Vec2(BLOBBY_MOVE_VELOCITY, body->GetLinearVelocity().y));
			} else {
				body->ApplyForce(b2Vec2(BLOBBY_MOVE_VELOCITY, 0), body->GetPosition());
			}
		}
	} 
	
	// Go to the next texture if enough time has elapsed.
	if (this->isOnGround && this->isWalking && glutGet(GLUT_ELAPSED_TIME) - this->previousTicks > BLOBBY_TEXTURE_CHANGE_FREQUENCY) {
		this->activeTexture++;
		if (this->activeTexture == 5) {
			this->activeTexture = 0;
		}
		this->previousTicks = glutGet(GLUT_ELAPSED_TIME);
	} else if (this->isDucking && glutGet(GLUT_ELAPSED_TIME) - this->previousTicks > BLOBBY_TEXTURE_CHANGE_FREQUENCY) {
		if (this->activeTexture < 4) {
			this->activeTexture++;
		}
	} else if (!this->isDucking && (!this->isOnGround || !this->isWalking)) {
		this->activeTexture = 0;
	}

	// Duck and cover. ;-)
	if (this->isDucking || this->isStandingUp) {
		b2CircleShape *shape = (b2CircleShape*)this->bodies.at(0)->GetFixtureList()->GetNext()->GetShape();
		if (this->isDucking && shape->m_p.y != (BLOBBY_CENTER_DISTANCE / 2.0f)) {
			shape->m_p.Set(shape->m_p.x, max(BLOBBY_CENTER_DISTANCE / 2.0f, shape->m_p.y - 0.02f));
			/*if (shape->m_p.y == BLOBBY_CENTER_DISTANCE / 2.0f) {
				this->isDucking = false;
			}*/
		} else if (this->isDucking == false) {
			shape->m_p.Set(shape->m_p.x, min(BLOBBY_CENTER_DISTANCE, shape->m_p.y + 0.02f));
			if (shape->m_p.y == BLOBBY_CENTER_DISTANCE) {
				this->isStandingUp = false;
			}
		}
	}

	// set direction to unknown again if blobby is not moving
	if (this->isWalking == false && this->movementDirection != DIRECTION_UNKNOWN
		&& abs(this->getBody(0)->GetLinearVelocity().x) < 3.0f)
	{
		debug("set direction to unknown");
		this->movementDirection = DIRECTION_UNKNOWN;
	}
}

void Blobby::update(Publisher *who, UpdateData *what)
{
	if (this->isDead || this->controller == 0) {
		return;
	}

	ContactEventArgs *contactEventArgs = dynamic_cast<ContactEventArgs*>(what);
	if (contactEventArgs != 0)
	{
		// Did we hit or cease to hit the ground?
		b2Fixture *blobbyFixture = 0;
		b2Fixture *contactFixture = 0;
		// Sort the fixtures.
		if (contactEventArgs->contact->GetFixtureA()->GetBody() == this->bodies.at(0)) {
			blobbyFixture = contactEventArgs->contact->GetFixtureA();
			contactFixture = contactEventArgs->contact->GetFixtureB();
		} else if (contactEventArgs->contact->GetFixtureB()->GetBody() == this->bodies.at(0)) {
			contactFixture = contactEventArgs->contact->GetFixtureA();
			blobbyFixture = contactEventArgs->contact->GetFixtureB();
		}
		if (contactFixture != 0)
		{
			// There is a fixture which might be a ground.
			IEntity *entity = (IEntity*)contactFixture->GetBody()->GetUserData();
			if (entity != 0)
			{
				if (blobbyFixture == this->lowerFixture)
				{
					// It is the lower shape, so we need to cope with the
					// contact point angle.
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
								contactPoint->fixture = contactFixture;
								contactPoint->angle = radian2degree(angle);
								this->contactPoints.push_back(contactPoint);
							}
						}
					} 
					else if (contactEventArgs->type == CONTACT_TYPE_END)
					{
						// The contact has ended. We need to remove the ContactPoint.
						list<ContactPoint*> destroyableContactPoints;
						for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
							ContactPoint *cp = *it;
							if (cp->fixture == contactFixture) {
								destroyableContactPoints.push_back(cp);
							}
						}
						for (list<ContactPoint*>::iterator it = destroyableContactPoints.begin(); it != destroyableContactPoints.end(); ++it) {
							this->contactPoints.remove(*it);
						}
					}
				}
				else if (blobbyFixture == this->upperFixture)
				{
					// It is the upper shape, so we just stop jumping.
					if (contactEventArgs->type == CONTACT_TYPE_BEGIN)
					{
						this->isJumping = false;
						this->isRotating = false;
						debug("lol");
					}
				}
			}
		}
	}
}

void Blobby::draw()
{
	float x = this->getBody(0)->GetPosition().x;
	float y = this->getBody(0)->GetPosition().y;
	float angle = this->getBody(0)->GetAngle();
	int width = 0; // proportional scaling!
	int height = int(meter2pixel(BLOBBY_CENTER_DISTANCE + BLOBBY_UPPER_RADIUS + BLOBBY_LOWER_RADIUS));
	if (this->isDead) {
		Texturizer::draw(this->getTexture(this->activeTexture), x, y + BLOBBY_UPPER_RADIUS / 2, angle, width, height, false, true, 0, new Color(255, 255, 255, this->opacity));
	} else
	{
		// the error comes with "y + BLOBBY_UPPER_RADIUS / 2"... this offset is not anymore correct when blobby rotates
		/*b2Vec2 angle_vec = b2Vec2(cos(angle), sin(angle));
		b2Vec2 offset = b2Vec2(0, (BLOBBY_UPPER_RADIUS / 2));
		//offset = offset * angle_vec;
		
		b2Vec2 offset2 = offset * angle_vec;

		b2Vec2 pos_blobby = b2Vec2(x, y);
		b2Vec2 pos_blobby_image = pos_blobby + offset;*/

		//Texturizer::draw(this->getTexture(this->activeTexture), pos_blobby_image.x, pos_blobby_image.y, angle, width, height, false, true);
		Texturizer::draw(this->getTexture(this->activeTexture), x, y + BLOBBY_UPPER_RADIUS / 2, angle, width, height, false, true);
	}

	if (!this->isDead && this->getHealth() < this->getMaxHealth()) {
		b2Vec2 pos = meter2pixel(this->getBody(0)->GetPosition()) + b2Vec2(0.0f, height - 4.0f);
		x = pos.x;
		y = pos.y;

		float offset = float(this->getHealth()) / float(this->getMaxHealth());
		glEnable(GL_BLEND);
		glBlendFunc (GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
		glColor4f(1.0f - offset, offset, 0.0f, 0.8f);
		glBegin(GL_TRIANGLE_FAN);
			glVertex2f(x - 12.0f, y + 0.0f);
			glVertex2f(x - 12.0f + 24.0f * offset, y + 0.0f);
			glVertex2f(x - 12.0f + 24.0f * offset, y + 4.0f);
			glVertex2f(x - 12.0f, y + 4.0f);
		glEnd();
		glDisable(GL_BLEND);

		glColor4f(1.0f, 1.0f, 1.0f, 0.2f);
		glBegin(GL_LINE_LOOP);
			glVertex2f(x - 12.0f, y + 0.0f);
			glVertex2f(x + 12.0f, y + 0.0f);
			glVertex2f(x + 12.0f, y + 4.0f);
			glVertex2f(x - 12.0f, y + 4.0f);
		glEnd();
	}
	
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
	this->nextWeapon = weapon;
}

AbstractWeapon* Blobby::getWeapon()
{
	return this->weapon;
}

void Blobby::jump()
{
	b2Body *body = this->bodies.at(0);
	if (this->isOnGround && !this->isJumping) {
		// The blobby is not jumping yet.
		if (this->isOnGround) {
			// The blobby is on the ground, i.e. jump!
			float x = body->GetLinearVelocity().x;
			body->SetLinearVelocity(b2Vec2(0, 0));
			body->ApplyForce(b2Vec2(x / 2, BLOBBY_JUMP_FORCE), body->GetPosition());
			this->isJumping = true;
		}
	} else if (!this->isOnGround && this->isJumping && !this->isRotating) {
		// Enable rotation on double jump (+ boost).
		body->ApplyForce(b2Vec2(0.0f, BLOBBY_JUMP_BOOST_FORCE), body->GetPosition());
		this->isRotating = true;

		// if blobby is running, we rotate in running direction. if blobby is standing, we rotate in direction blobby is looking
		if (this->movementDirection != DIRECTION_UNKNOWN)
		{
			this->rotationDirection = this->movementDirection;
			debug("roate: use run direction");
		}
		else
		{
			this->rotationDirection = this->getViewingDirection();
			debug("roate: use view direction");
		}
	}
}

void Blobby::walkLeft()
{
	this->movementDirection = DIRECTION_LEFT;
	this->isWalking = true;
}

void Blobby::walkRight()
{
	this->movementDirection = DIRECTION_RIGHT;
	this->isWalking = true;
}

void Blobby::stopWalk()
{
	if (this->isWalking && this->isOnGround) {
		// The blobby is walking on ground, so we stop it and apply
		// a low linear force to make it smooth.
		b2Body *body = this->bodies.at(0);
		body->SetLinearVelocity(b2Vec2(0.0f, body->GetLinearVelocity().y));
		switch (this->movementDirection) {
		case DIRECTION_RIGHT:
			debug("stopping smooth");
			body->ApplyForce(b2Vec2(BLOBBY_MOVE_STOP_FORCE, 0.0f), body->GetWorldCenter());
			break;
		case DIRECTION_LEFT:
			debug("stopping smooth");
			body->ApplyForce(b2Vec2(-BLOBBY_MOVE_STOP_FORCE, 0.0f), body->GetWorldCenter());
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

void Blobby::setHealth(int health)
{
	this->health = health;
}

int Blobby::getHealth()
{
	return this->health;
}

void Blobby::setMaxHealth(int maxHealth)
{
	this->maxHealth = maxHealth;
}

int Blobby::getMaxHealth()
{
	return this->maxHealth;
}

inline float correctAngle(float angle, float rotation)
{
	return angle;// - rotation;
}

bool Blobby::checkIsOnGround()
{
	// A blobby is on ground if the contact point is in a GROUND_ANGLE
	// wide angle that is equally spanned around the vector pointing
	// from the center of the lower circle shape to its bottom
	// (negative y-axis direction).
	for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
		ContactPoint *contactPoint = *it;
		float angle = correctAngle(contactPoint->angle, radian2degree(this->bodies.at(0)->GetAngle()));
		if (90 - GROUND_ANGLE / 2 <= angle && angle <= 90 + GROUND_ANGLE / 2) {
			return true;
		}
	}
	return false;
}

bool Blobby::checkIsTouchingWall(int *wallDirection)
{
	// A blobby touches a wall if the contact point is outside of a
	// GROUND_ANGLE wide angle that is equally spanned around the
	// vector pointing from the center of the lower circle shape to
	// its bottom (negative y-axis direction).
	for (list<ContactPoint*>::iterator it = this->contactPoints.begin(); it != this->contactPoints.end(); ++it) {
		ContactPoint *contactPoint = *it;
		float angle = correctAngle(contactPoint->angle, radian2degree(this->bodies.at(0)->GetAngle()));
		if (angle < 90 - GROUND_ANGLE / 2 || 90 + GROUND_ANGLE / 2 < angle) {
			*wallDirection = angle > 90 + GROUND_ANGLE / 2 && angle < 270 ? DIRECTION_LEFT : DIRECTION_RIGHT;
			return true;
		}
	}
	*wallDirection = DIRECTION_UNKNOWN;
	return false;
}