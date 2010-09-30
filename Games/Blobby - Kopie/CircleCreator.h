#pragma once

#include "Box2D.h"

#include "GameObjectCreator.h"
#include "Circle.h"

class CircleCreator :
	public GameObjectCreator
{
public:
	Circle* Create(GameObjectSettings settings);
	GameObjectSettings GetDefaultSettings();
	int GetObjectCount();
};
