#pragma once

#include <Box2D.h>

#include "GameObject.h"

class Ground :
	public GameObject
{
	friend class GroundCreator;
public:
	Ground(void);
	~Ground(void);
};
