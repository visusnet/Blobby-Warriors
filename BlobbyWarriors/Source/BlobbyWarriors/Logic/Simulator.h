#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <GL/glut.h>

#include <Box2D.h>

#include "../Debug.h"
#include "Level.h"
#include "Controller\PlayerController.h"
#include "../Model/GameWorld.h"
#include "../Model/PhysicsUtils.h"
#include "../Model/Entity/Factory/BlobbyFactory.h"

class Simulator
{
public:
	Simulator();
	~Simulator();
	void step();
private:
	Level *level;
	GameWorld *gameWorld;
	Blobby *playerBlobby;
};

#endif