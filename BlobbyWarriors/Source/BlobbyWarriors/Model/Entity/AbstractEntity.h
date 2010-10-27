#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <Box2D.h>

#include "../PhysicsUtils.h"
#include "IEntity.h"
#include "../../Debug.h"

class AbstractEntity : public IEntity
{
public:
	virtual void draw();
};

#endif