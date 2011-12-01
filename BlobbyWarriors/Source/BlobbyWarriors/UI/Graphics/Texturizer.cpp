#include "Texturizer.h"

void Texturizer::draw(Texture *texture, float x, float y, float angle, int width, int height, bool flip, bool keepProportion, BlendingInfo *blending, Color *color)
{
	// Enable texturing.
	glEnable(GL_TEXTURE_2D);

	// Bind the texture for drawing.
	texture->bind();

	if (blending != 0) {
		if (blending->isEnabled) {
			glEnable(GL_BLEND);
			glBlendFunc(blending->sfactor, blending->dfactor);
		}
	} else {
		// Enable alpha blending by default.
		glEnable(GL_BLEND);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	}
	
	// Create a copy of the given values.
	int w = width;
	int h = height;	

	if (w == 0) {
		// No width is given, take width of texture.
		width = texture->getWidth();
	} else if (h == 0 && keepProportion) {
		// Width is given, but height is not. Calculate height.
		float ratio = float(texture->getWidth()) / float(texture->getHeight());
		height = round(width / ratio);
	}
	if (h == 0) {
		// No height is given, take height of texture.
		height = texture->getHeight();
	} else if (w == 0 && keepProportion) {
		// Height is given, but width is not. Calculate width.
		float ratio = float(texture->getWidth()) / float(texture->getHeight());
		width = round(height * ratio);
	}

	// Create centered dimension vectors.
	b2Vec2 vertices[4];

	if (flip)
	{
		vertices[3] = 0.5f * b2Vec2(- float(width), - float(height));
		vertices[2] = 0.5f * b2Vec2(+ float(width), - float(height));
		vertices[1] = 0.5f * b2Vec2(+ float(width), + float(height));
		vertices[0] = 0.5f * b2Vec2(- float(width), + float(height));
	}
	else
	{
		vertices[0] = 0.5f * b2Vec2(- float(width), - float(height));
		vertices[1] = 0.5f * b2Vec2(+ float(width), - float(height));
		vertices[2] = 0.5f * b2Vec2(+ float(width), + float(height));
		vertices[3] = 0.5f * b2Vec2(- float(width), + float(height));
	}

	b2Mat22 matrix = b2Mat22();
	matrix.Set(angle);

	if (color != 0) {
		glColor4ub(color->r, color->g, color->b, color->a);
	} else {
		glColor3f(1.0f, 1.0f, 1.0f);
	}

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
