#pragma once

#include "Box2D.h"

#include "GameObjectCreator.h"
#include "Blobby.h"

class BlobbyCreator :
	public GameObjectCreator
{
public:
	Blobby* Create(GameObjectSettings settings);
	GameObjectSettings GetDefaultSettings();
	int GetObjectCount();
};
