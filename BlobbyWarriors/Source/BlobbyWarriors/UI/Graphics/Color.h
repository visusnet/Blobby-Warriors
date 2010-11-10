#ifndef COLOR_H
#define COLOR_H

#include <GL/glut.h>

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

#endif