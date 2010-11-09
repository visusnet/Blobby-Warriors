#ifndef SKATEBOARD_H
#define SKATEBOARD_H

class Skateboard;

#include "AbstractEntity.h"
#include "../../Debug.h"

class Skateboard : public AbstractEntity
{
public:
	void draw();
};

#endif