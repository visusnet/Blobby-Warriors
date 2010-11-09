#include "Texture.h"

Texture::Texture(int width, int height)
{
	glGenTextures(1, &this->textureId);

	this->width = width;
	this->height = height;
}

int Texture::getWidth()
{
	return this->width;
}

int Texture::getHeight()
{
	return this->height;
}

void Texture::initFilter()
{
	// We will use linear interpolation for magnification filter.
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	// We will use linear interpolation for minifying filter.
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

void Texture::unpack()
{
	glPixelStoref(GL_UNPACK_ALIGNMENT, 1);
}

void Texture::bind()
{
	glBindTexture(GL_TEXTURE_2D, this->textureId);
}

Texture::~Texture()
{
	glDeleteTextures(1, &this->textureId);
}
