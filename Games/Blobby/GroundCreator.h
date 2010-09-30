#pragma once

#include "Box2D.h"

#include "GameObjectCreator.h"
#include "Ground.h"

class GroundCreator :
	public GameObjectCreator
{
public:
	Ground* Create(GameObjectSettings settings);
	GameObjectSettings GetDefaultSettings();
	int GetObjectCount();
};
