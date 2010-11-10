#ifndef TEXTURELOADER_H
#define TEXTURELOADER_H

#include <IL/ilut.h>

#include "GraphicsUtils.h"
#include "Image.h"
#include "Texture.h"
#include "Color.h"
#include "../../Debug.h"

class TextureLoader
{	
public:
	static void initialize();
	static Texture* createTexture(wchar_t *filename, Color *color = 0, Color *colorKey = 0);
private:
	static void setColorKey(ILubyte *imageData, int size, Color *color);
	static void colorize(ILubyte *imageData, int size, Color *color);
};

#endif