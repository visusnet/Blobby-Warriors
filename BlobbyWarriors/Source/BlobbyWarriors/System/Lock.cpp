#include "Lock.h"

Lock::Lock(Mutex& mutex) : mutex(mutex)
{
    this->mutex.acquire();
}

Lock::~Lock ()
{
	this->mutex.release();
}