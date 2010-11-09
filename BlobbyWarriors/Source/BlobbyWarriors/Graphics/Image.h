#ifndef IMAGE_H
#define IMAGE_H

#include <iostream>

#include <IL/ilut.h>

using namespace std;

class Image
{
public:
	Image();
	~Image();
	ILint getWidth();
	ILint getHeight();
	ILint getDepth();
	ILint getBpp();
	ILint getFormat();
	ILubyte* getData();
	bool loadFromFile(wchar_t *filename);
	bool convert();
	bool scale(ILint width, ILint height, ILint format);
	void bind();
private:
	ILuint imageId;
};

#endif