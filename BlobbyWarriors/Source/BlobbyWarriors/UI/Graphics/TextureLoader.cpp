#include "TextureLoader.h"

void TextureLoader::initialize()
{
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION) {
		debug("Wrong DevIL version detected.");
		return;
	}

	ilInit();
//	iluInit();
	ilutRenderer(ILUT_OPENGL);
}

Texture* TextureLoader::createTexture(wchar_t *filename, Color *color, Color *colorKey)
{
	// Generate some space for an image and bind it.
	Image *image = new Image();
	image->bind();
	
	bool retval = image->loadFromFile(filename);
	if (!retval) {
		debug("Could not load image from file.");
		return 0;
	}

	ILint format = image->getFormat();

	retval = image->convert();
	if (!retval) {
		debug("Could not convert image from RGBA to unsigned byte");
	}

	int width = image->getWidth();
	int height = image->getHeight();
	int pWidth = getNextPowerOfTwo(width);
	int pHeight = getNextPowerOfTwo(height);
	
	retval = image->scale(pWidth, pHeight, image->getDepth());
	if (!retval) {
		debug("Could not scale image from (w: %i, h: %i) to (w: %i, h: %i) with depth %i.", image->getWidth(), image->getHeight(), pWidth, pHeight, image->getDepth());
		return 0;
	}

	// Correct upside down images.
	image->flip();

	// Generate some space for a texture and bind it.
	Texture *texture = new Texture(width, height);
	texture->bind();

	// Set the interpolation filters.
	texture->initFilter();

	// Unpack pixels.
	texture->unpack();

	ILubyte *imageData = image->getData();

	int size = image->getWidth() * image->getHeight();
	if (colorKey != 0) {
		TextureLoader::setColorKey(imageData, size, colorKey);
	}
	if (color != 0) {
		TextureLoader::colorize(imageData, size, color);
	}
	
	// Map image data to texture data.
	glTexImage2D(GL_TEXTURE_2D, 0, image->getBpp(), image->getWidth(), image->getHeight(), 0, image->getFormat(), GL_UNSIGNED_BYTE, imageData);

	delete image;

	return texture;
}

void TextureLoader::setColorKey(ILubyte *imageData, int size, Color *color)
{
	for (int i = 0; i < size * 4; i += 4) {
		if (imageData[i] == color->r && imageData[i + 1] == color->g && imageData[i + 2] == color->b) {
			imageData[i + 3] = 0;
		}
	}
}

void TextureLoader::colorize(ILubyte *imageData, int size, Color *color)
{
	for (int i = 0; i < size * 4; i += 4) {
		int rr = (int(imageData[i]) * int(color->r)) >> 8;
		int rg = (int(imageData[i + 1]) * int(color->g)) >> 8;
		int rb = (int(imageData[i + 2]) * int(color->b)) >> 8;
		int fak = int(imageData[i]) * 5 - 4 * 256 - 138;

		if (fak > 0) {
			rr += fak;
			rg += fak;
			rb += fak;
		}

		rr = rr < 255 ? rr : 255;
		rg = rg < 255 ? rg : 255;
		rb = rb < 255 ? rb : 255;

		imageData[i] = rr > 0 ? (GLubyte) rr : 1;
		imageData[i + 1] = rg > 0 ? (GLubyte) rg : 1;
		imageData[i + 2] = rb > 0 ? (GLubyte) rb : 1;
	}
}