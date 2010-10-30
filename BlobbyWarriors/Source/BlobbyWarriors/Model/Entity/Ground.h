#ifndef GROUND_H
#define GROUND_H

class Ground;

#include "AbstractEntity.h"
#include "../../Debug.h"

class Ground : public AbstractEntity
{
public:
	void draw();
};

#endif