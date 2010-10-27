#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <GL/glut.h>

#include <Box2D.h>

#include "../Debug.h"
#include "Level.h"
#include "PhysicsUtils.h"

class Simulator
{
public:
	Simulator();
	~Simulator();
	void step();
private:
	Level *level;
	b2World *world;
	b2Body *mainBody;
};

#endif