#include "Texturizer.h"

void Texturizer::draw(Texture *texture, float x, float y, float angle)
{
	// Enable texturing.
	glEnable(GL_TEXTURE_2D);

	// Bind the texture for drawing.
	texture->bind();

	// Enable alpha blending.
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	
	int width = texture->getWidth();
	int height = texture->getHeight();

	// Create centered dimension vectors.
	b2Vec2 vertices[4];
	vertices[0] = 0.5f * b2Vec2(- width, - height);
	vertices[1] = 0.5f * b2Vec2(+ width, - height);
	vertices[2] = 0.5f * b2Vec2(+ width, + height);
	vertices[3] = 0.5f * b2Vec2(- width, + height);

	b2Mat22 matrix = b2Mat22();
	matrix.Set(angle);

	glColor3i(255, 255, 255);

	glBegin(GL_QUADS);
	for (int i = 0; i < 4; i++) {
		float texCoordX = i == 0 || i == 3 ? 1.0f : 0.0f;
		float texCoordY = i < 2 ? 1.0f : 0.0f;
		glTexCoord2f(texCoordX, texCoordY);

		// Rotate and move vectors.
		b2Vec2 vector = b2Mul(matrix, vertices[i]) + meter2pixel(b2Vec2(x, y));
		glVertex2f(vector.x, vector.y);
	}
	glEnd();

	glDisable(GL_BLEND);
	glDisable(GL_TEXTURE_2D);
}