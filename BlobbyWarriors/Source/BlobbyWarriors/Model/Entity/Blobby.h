#ifndef BLOBBY_H
#define BLOBBY_H

class Blobby;

#include <vector>

#include <GL/glut.h>

#include "AbstractEntity.h"
#include "AbstractWeapon.h"
#include "Factory/BlobbyFactory.h"
#include "../../PublishSubscribe.h"
#include "../../Graphics/GraphicsEngine.h"
#include "../../Logic/ContactListener.h"
#include "../../Logic/Controller/IController.h"
#include "../../Logic/Controller/PlayerController.h"
#include "../../Debug.h"

using namespace std;

#define DIRECTION_UNKNOWN 0
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2

#define BLOBBY_UPPER_RADIUS pixel2meter(14.0f /* px */)
#define BLOBBY_LOWER_RADIUS pixel2meter(17.0f /* px */)
#define BLOBBY_CENTER_DISTANCE pixel2meter(16.0f /* px */)

#define BLOBBY_JUMP_FORCE 920.0f
#define BLOBBY_JUMP_BOOST_FORCE 480.0f
#define BLOBBY_MOVE_VELOCITY 14.0f
#define BLOBBY_MOVE_STOP_FORCE 400.0f

#define GROUND_ANGLE 160 /* degrees */

struct ContactPoint
{
	b2Fixture *fixture;
	float angle;
};

class Blobby : public AbstractEntity, public Subscriber
{
public:
	Blobby();
	void step();
	void draw();
	void update(Publisher *who, UpdateData *what = 0);
	void setController(IController *controller);
	void addWearable(IWearable *wearable);
	IWearable* getWearable(unsigned int i);
	unsigned int getWearableCount();
	void setWeapon(AbstractWeapon *weapon);
	AbstractWeapon* getWeapon();
	void jump();
	void walkLeft();
	void walkRight();
	void stopWalk();
	void duck();
	void standUp();
private:
	bool checkIsOnGround();
	bool checkIsTouchingWall(int *wallDirection);

	IController *controller;
	vector<IWearable*> wearables;
	AbstractWeapon *weapon;
	bool isJumping;
	bool isRotating;
	bool isWalking;
	bool isDucking;
	bool isStandingUp;
	bool isOnGround;
	bool isTouchingWall;
	float angle;
	int direction;
	int wallDirection;
	list<ContactPoint*> contactPoints;

	b2Fixture *upperFixture;
	b2Fixture *lowerFixture;

	Texture *texture;

	friend class BlobbyFactory;
};

#endif