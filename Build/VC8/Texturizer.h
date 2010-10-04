#ifndef TEXTURIZER_H
#define TEXTURIZER_H

#include "IL/il.h"
#include "IL/ilut.h"

#include "Box2D.h"

#include "RigidBody.h"
#include "TextureLoader.h"

class Texturizer
{
public:
	~Texturizer();
	void LoadImages(RigidBody *rigidBody);
	void Draw(int id, float x, float y, int w, int h, float angle);

	TextureLoader *textureLoader;
	Texture *textures;
};

#endif
