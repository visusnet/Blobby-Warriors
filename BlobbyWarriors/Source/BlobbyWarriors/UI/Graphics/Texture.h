#ifndef TEXTURE_H
#define TEXTURE_H

#include <GL/glut.h>

class Texture
{
public:
	Texture(int width, int height);
	~Texture();
	int getWidth();
	int getHeight();
	void initFilter();
	void unpack();
	void bind();
private:
	GLuint textureId;
	int width;
	int height;
};

#endif