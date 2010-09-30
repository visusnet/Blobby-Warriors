#pragma once

#include "Box2D.h"

#include "GameObjectCreator.h"
#include "Box.h"

class BoxCreator :
	public GameObjectCreator
{
public:
	Box* Create(GameObjectSettings settings);
	GameObjectSettings GetDefaultSettings();
	int GetObjectCount();
};
