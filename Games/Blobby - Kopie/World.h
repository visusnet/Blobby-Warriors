#pragma once

#include <iostream>
#include <cstdlib>

#include <Box2D.h>

#include "DebugDraw.h"
#include "GameObjectCreator.h"
#include "BoxCreator.h"
#include "GroundCreator.h"
#include "CircleCreator.h"
#include "BlobbyCreator.h"

#include "Player.h"

using namespace std;

class World
{
public:
	static World* GetInstance();
	void Initialize();
	void Step();
	b2World *GetPhysicsWorld();
private:
	World();
	~World();
	static World *instance;
	b2World *physicsWorld;
	b2Body *body;
};
