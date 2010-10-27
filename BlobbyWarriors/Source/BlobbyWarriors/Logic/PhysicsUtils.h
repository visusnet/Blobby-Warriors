#ifndef PHYSICSUTILS_H
#define PHYSICSUTILS_H

#include <Box2D.h>

#define SCALING_FACTOR 30.0f

inline b2Vec2 pixel2meter(b2Vec2 vector)
{
	return (1.0f / SCALING_FACTOR) * vector;
}

inline float pixel2meter(float pixel)
{
	return pixel * (1.0f / SCALING_FACTOR);
}

inline b2Vec2 meter2pixel(b2Vec2 vector)
{
	return SCALING_FACTOR * vector;
}

inline float meter3pixel(float meter)
{
	return meter * SCALING_FACTOR;
}

#endif