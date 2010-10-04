#include "Texturizer.h"

// Deprecated
#define TEXTURE_COUNT 5

Texturizer::~Texturizer()
{
	//for (int i = 0; i < sizeof(this->textures) / sizeof(glTexture); i++)
	//{
	//	this->textureLoader->FreeTexture(&this->textures[i]);
	//}
}

void Texturizer::LoadImages(RigidBody *rigidBody)
{
	bool failed = false;
	this->textureLoader = new TextureLoader();

	this->textures = (Texture *) malloc(rigidBody->GetTextureCount() * sizeof(Texture));

	for (int i = 0; i < rigidBody->GetTextureCount(); i++)
	{
		if (!this->textureLoader->LoadImage("Blobby Warriors\\Data\\blobby\\01.bmp", &this->textures[0]))
		{
			failed = true;
		}
	}
	
	if (failed)
	{
		printf("ERROR: Could not load images.\n");
	}
	else
	{
		rigidBody->SetTextures(this->textures);

		printf("Images loaded successfully\n");
	}
}

#define SCALING_FACTOR 15
#define FACTOR (2 * SCALING_FACTOR)

void Texturizer::Draw(int id, float x, float y, int w, int h, float angle)
{
	glEnable(GL_TEXTURE_2D);

	glBindTexture(GL_TEXTURE_2D, this->textures[id].GLid);

	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

	w = (int)this->textures[id].width;
	h = (int)this->textures[id].height;

	b2Vec2 vertices[4];
	vertices[0] = b2Vec2((float) - w / FACTOR, (float) - h / FACTOR);
	vertices[1] = b2Vec2((float) + w / FACTOR, (float) - h / FACTOR);
	vertices[2] = b2Vec2((float) + w / FACTOR, (float) + h / FACTOR);
	vertices[3] = b2Vec2((float) - w / FACTOR, (float) + h / FACTOR);

	b2Mat22 matrix = b2Mat22();
	matrix.Set(angle);

	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++)
	{
		glTexCoord2f(i == 0 || i == 3 ? 0.0f : 1.0f,
					 i < 2 ? 0.0f : 1.0f);

		if (angle != 0)
		{
			b2Vec2 vector = b2Mul(matrix, vertices[i]) + b2Vec2(x, y);
			glVertex2f(vector.x, vector.y);
		}
		else
		{
			glVertex2f(vertices[i].x + x, vertices[i].y + y);
		}
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}