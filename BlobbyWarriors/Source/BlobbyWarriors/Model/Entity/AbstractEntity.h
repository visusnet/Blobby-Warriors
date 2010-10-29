#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <vector>

#include <GL/glut.h>
#include <Box2D.h>

#include "../GameWorld.h"
#include "../PhysicsUtils.h"
#include "IEntity.h"
#include "../../Debug.h"

using namespace std;

class AbstractEntity : public IEntity
{
public:
	AbstractEntity();
	virtual void draw();
	void destroy();
	void addBody(b2Body *body);
	b2Body* getBody(unsigned int i);
	unsigned int getBodyCount();
protected:
	vector<b2Body*> bodies;
};

#endif