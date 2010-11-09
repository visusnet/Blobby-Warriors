#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <IL/ilut.h>

#include "GraphicsUtils.h"
#include "Image.h"
#include "Texture.h"
#include "../Debug.h"

class Color
{
public:
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a = 0) {
		this->r = r;
		this->g = g;
		this->b = b;
		this->a = a;
	}
};

class TextureLoader
{	
public:
	static void initialize();
	static Texture* createTexture(wchar_t *filename, Color *color = 0);
private:
	static void setColorKey(ILubyte *imageData, int size, Color *color);
	static void colorize(ILubyte *imageData, int size, Color *color);
};

#endif