#ifndef THREAD_H
#define THREAD_H

#include <Windows.h>

class Thread
{
public:
	Thread(unsigned long (__stdcall *fun)(void *arg), void* arg);
	~Thread();
	void resume();
	void waitForDeath();
private:
	void *handle;
	unsigned long tid;
};

#endif