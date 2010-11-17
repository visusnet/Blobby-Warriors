#ifndef BOX_H
#define BOX_H

class Box;

#include "AbstractEntity.h"
#include "../../Debug.h"

class Box : public AbstractEntity
{
public:
	void draw();
};

#endif