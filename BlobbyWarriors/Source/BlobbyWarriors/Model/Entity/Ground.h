#ifndef GROUND_H
#define GROUND_H

#include "AbstractEntity.h"
#include "../../Debug.h"

class Ground : public AbstractEntity
{
public:
	void setBody(b2Body *body);
	void draw();
private:
	b2Body *body;
};

#endif