#ifndef TEXTURE_LOADER_H
#define TEXTURE_LOADER_H

#include "IL/il.h"
#include "IL/ilut.h"

#include "Box2D.h"

#include "Color.h"

struct Texture
{
	ILuint ILid;
	GLuint GLid;
	double width;
	double height;
	int pwidth;
	int pheight;
};

class TextureLoader
{
public:
	TextureLoader();
	bool LoadImage(char *filename, Texture *texture);

private:
	static int Round(double x);
	static int NextPowerOfTwo(int x);
	void SetColorKey(ILubyte *imageData, int size, Color *color);
	void Colorize(ILubyte *imageData, int size, Color *color);
	inline int TextureLoader::Shift(int x);
};

#endif
