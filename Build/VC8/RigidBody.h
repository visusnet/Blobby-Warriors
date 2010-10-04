#ifndef RIGID_BODY_WRAPPER_H
#define RIGIT_BODY_WRAPPER_H

#include "Box2D.h"

#include "TextureLoader.h"

#pragma once

enum BodyType
{
	BLOBBY=1,
	GROUND=2
};

class RigidBody
{
public:
	virtual void SetTextures(Texture *textures) { textures; };
	virtual GLuint GetTexture() { return 0; };
	virtual int GetTextureCount() { return 0; };
	virtual char** GetTextureFileNames() { return NULL; };
	BodyType type;
};

#endif
