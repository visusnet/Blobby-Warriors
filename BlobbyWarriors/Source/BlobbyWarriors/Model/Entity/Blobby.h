#ifndef BLOBBY_H
#define BLOBBY_H

#include <vector>

#include <GL/glut.h>

class Blobby;

#include "AbstractEntity.h"
#include "AbstractWeapon.h"
#include "../../Logic/Controller/IController.h"
#include "../../Debug.h"

using namespace std;

class Blobby : public AbstractEntity
{
public:
	void setController(IController *controller);
	void draw();
	void addWearable(IWearable *wearable);
	IWearable* getWearable(unsigned int i);
	unsigned int getWearableCount();
	void setWeapon(AbstractWeapon *weapon);
	AbstractWeapon* getWeapon();
private:
	IController *controller;
	vector<IWearable*> wearables;
	AbstractWeapon *weapon;
};

#endif