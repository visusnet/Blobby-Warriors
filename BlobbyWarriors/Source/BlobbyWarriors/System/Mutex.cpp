#include "Mutex.h"

Mutex::Mutex()
{
	InitializeCriticalSection(&this->criticalSection);
}

Mutex::~Mutex()
{
	DeleteCriticalSection(&this->criticalSection);
}

void Mutex::acquire()
{
    EnterCriticalSection(&this->criticalSection);
}

void Mutex::release()
{
    LeaveCriticalSection(&this->criticalSection);
}
