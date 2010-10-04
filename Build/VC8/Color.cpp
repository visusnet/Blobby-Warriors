#include "Color.h"

Color::Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = a;
}

Color::Color(GLubyte r, GLubyte g, GLubyte b)
{
	this->r = r;
	this->g = g;
	this->b = b;
	this->a = 255;
}
