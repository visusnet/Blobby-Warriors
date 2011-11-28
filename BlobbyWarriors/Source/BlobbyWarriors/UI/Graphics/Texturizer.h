#ifndef TEXTURIZER_H
#define TEXTURIZER_H

#include <Box2D.h>

#include "../../Model/PhysicsUtils.h"
#include "GraphicsUtils.h"
#include "Texture.h"
#include "Color.h"
#include "../../Debug.h"

struct BlendingInfo
{
	bool isEnabled;
	GLenum sfactor;
	GLenum dfactor;
};

class Texturizer
{
public:
	static void draw(Texture *texture, float x, float y, float angle = 0, int width = 0, int height = 0, bool keepProportion = false, BlendingInfo *blending = 0, Color *color = 0, bool flip = false);
};

#endif