#ifndef MUTEX_H
#define MUTEX_H

#include <Windows.h>

class Mutex;

#include "Lock.h"

class Mutex
{
public:
    Mutex();
    ~Mutex();
private:
    void acquire();
    void release();

    CRITICAL_SECTION criticalSection;

	friend class Lock;
};


#endif