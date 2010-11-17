#ifndef LOCK_H
#define LOCK_H

class Lock;

#include "Mutex.h"

class Lock
{
public:
    Lock(Mutex& mutex);
    ~Lock();
private:
    Mutex &mutex;
};


#endif