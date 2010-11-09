#ifndef TEXTURIZER_H
#define TEXTURIZER_H

#include <Box2D.h>

#include "../Model/PhysicsUtils.h"
#include "Texture.h"

class Texturizer
{
public:
	static void draw(Texture *texture, float x, float y, float angle);
};

#endif