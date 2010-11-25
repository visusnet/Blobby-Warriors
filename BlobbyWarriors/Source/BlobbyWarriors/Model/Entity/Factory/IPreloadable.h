#ifndef IPRELOADABLE_H
#define IPRELOADABLE_H

#include "EntityFactory.h"

class IPreloadable
{
public:
	virtual void preload(EntityProperties& properties) = 0;
};

#endif