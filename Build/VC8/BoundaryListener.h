#ifndef BOUNDARY_LISTENER_H
#define BOUNDARY_LISTENER_H

#include "Box2D.h"

class Game;

class BoundaryListener : public b2BoundaryListener	
{
public:
	void Violation(b2Body* body);

	Game* game;
};

#include "Game.h"

#endif
