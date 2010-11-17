#include "Thread.h"

Thread::Thread(unsigned long (__stdcall *fun)(void *arg), void* arg)
{
	this->handle = CreateThread(0, // Security attributes
								0, // Stack size
								fun,
								arg,
								CREATE_SUSPENDED,
								&this->tid);
}

Thread::~Thread()
{
	CloseHandle(this->handle);
}

void Thread::resume()
{
	ResumeThread(this->handle);
}

void Thread::waitForDeath()
{
	WaitForSingleObject(this->handle, 2000);
}