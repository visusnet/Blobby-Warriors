#pragma once

#include <Box2D.h>

#include "GameObject.h"

class Circle :
	public GameObject
{
	friend class CircleCreator;
public:
	Circle(void);
	~Circle(void);
};
