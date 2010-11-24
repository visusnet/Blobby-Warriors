#ifndef GRAPHIC_H
#define GRAPHIC_H

class Graphic;

#include "AbstractEntity.h"
#include "../../Debug.h"

class Graphic : public AbstractEntity
{
public:
	void draw();
	void setX(float x);
	float getX();
	void setY(float y);
	float getY();
	void setAngle(float angle);
	float getAngle();
	void setWidth(float width);
	float getWidth();
	void setHeight(float height);
	float getHeight();
	void setDepth(float depth);
	float getDepth();
private:
	float x;
	float y;
	float angle;
	float width;
	float height;
	float depth;
};

#endif