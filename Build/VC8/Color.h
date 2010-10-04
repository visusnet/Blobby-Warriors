#ifndef COLOR_H
#define COLOR_H

#include "IL/il.h"
#include "IL/ilut.h"

class Color
{
public:
	Color(GLubyte r, GLubyte g, GLubyte b, GLubyte a);
	Color(GLubyte r, GLubyte g, GLubyte b);
	GLubyte r;
	GLubyte g;
	GLubyte b;
	GLubyte a;
};

#endif
