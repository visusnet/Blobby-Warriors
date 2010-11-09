#ifndef GRAPHICSUTILS_H
#define GRAPHICSUTILS_H

#include <cmath>

inline int round(double x)
{
	return (int)(x > 0 ? x + 0.5f : x - 0.5f);
}

inline int getNextPowerOfTwo(int x)
{
	double logbase2 = log((double)x) / log(2.0f);
	return round(pow(2, ceil(logbase2)));
}

#endif