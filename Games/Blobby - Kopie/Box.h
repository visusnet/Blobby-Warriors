#pragma once

#include <Box2D.h>

#include "GameObject.h"

class Box :
	public GameObject
{
	friend class BoxCreator;
public:
	Box(void);
	~Box(void);
};
