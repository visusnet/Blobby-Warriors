#ifndef TIMEABLE_H
#define TIMEABLE_H

#include <GL/glut.h>

class Timeable;

#include "Runnable.h"

#define TIMEABLE_DEFAULT_INTERVAL 1000

class Timeable : public Runnable
{
public:
	Timeable();
	void start();
	void setInterval(int interval);
	void setFrequency(double frequency);
protected:
	void run();
	virtual void tick() = 0;
private:
	int interval;
	int currentTime;
};

#endif