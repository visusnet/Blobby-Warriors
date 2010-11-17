#ifndef RUNNABLE_H
#define RUNNABLE_H

#include <Windows.h>

#include "Thread.h"

class Runnable
{
public:
	Runnable();
	virtual ~Runnable() {}
	void start();
	void kill();
protected:
	virtual void initThread() {};
	virtual void run() = 0;
	virtual void flushThread() {};

	static unsigned long __stdcall threadEntry(void *arg);

	int isDying;
	Thread thread;
};

#endif