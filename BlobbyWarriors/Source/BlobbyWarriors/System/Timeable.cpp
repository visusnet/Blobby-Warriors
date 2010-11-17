#include "Timeable.h"

Timeable::Timeable()
{
	this->interval = TIMEABLE_DEFAULT_INTERVAL;
	this->currentTime = glutGet(GLUT_ELAPSED_TIME);
}

void Timeable::start()
{
	this->thread.resume();
}

void Timeable::setInterval(int interval)
{
	this->interval = interval;
}

void Timeable::setFrequency(double frequency)
{
	this->interval = int(1.0 / frequency * 1000.0);
}

void Timeable::run()
{
	for (;;) {
		int now = glutGet(GLUT_ELAPSED_TIME);
		if (now - this->currentTime > this->interval) {
			this->currentTime = now;
			this->tick();
		}
	}
}