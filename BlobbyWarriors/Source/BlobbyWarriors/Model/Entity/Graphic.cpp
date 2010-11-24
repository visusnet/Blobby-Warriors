#include "Graphic.h"

void Graphic::draw()
{
	Texturizer::draw(this->getTexture(0), this->x, this->y, this->angle, this->getTexture(0)->getWidth(), this->getTexture(0)->getHeight());
}

void Graphic::setX(float x)
{
	this->x = x;
}

float Graphic::getX()
{
	return this->x;
}

void Graphic::setY(float y)
{
	this->y = y;
}

float Graphic::getY()
{
	return this->y;
}

void Graphic::setAngle(float angle)
{
	this->angle = angle;
}

float Graphic::getAngle()
{
	return this->angle;
}

void Graphic::setWidth(float width)
{
	this->width = width;
}

float Graphic::getWidth()	
{
	return this->width;
}

void Graphic::setHeight(float height)
{
	this->height = height;
}

float Graphic::getHeight()
{
	return this->height;
}

void Graphic::setDepth(float depth)
{
	this->depth = depth;
}

float Graphic::getDepth()
{
	return this->depth;
}