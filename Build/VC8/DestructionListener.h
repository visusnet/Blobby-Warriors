#ifndef DESTRUCTION_LISTENER_H
#define DESTRUCTION_LISTENER_H

#include "Box2D.h"

class Game;

class DestructionListener : public b2DestructionListener
{
public:
	void SayGoodbye(b2Shape* shape) { B2_NOT_USED(shape); }
	void SayGoodbye(b2Joint* joint);

	Game* game;
};

#include "Game.h"

#endif
