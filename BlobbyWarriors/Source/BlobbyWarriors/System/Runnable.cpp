#include "Runnable.h"

Runnable::Runnable() : isDying(0),
#pragma warning(disable: 4355) // 'this' used before initialized
	thread(this->threadEntry, this)
#pragma warning(default: 4355)
{
}

void Runnable::start()
{
	this->thread.resume();
}

void Runnable::kill()
{
    this->isDying++;
    this->flushThread();
    this->thread.waitForDeath();
}

unsigned long __stdcall Runnable::threadEntry(void* arg)
{
	Runnable *runnable = (Runnable*)arg;
	runnable->initThread();
	runnable->run();
	return 0;
}
