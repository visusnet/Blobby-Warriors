#ifndef IENTITY_H
#define IENTITY_H

#include <Box2D.h>

#define COLLISION_GROUP_BLOBBY -8
#define COLLISION_GROUP_GROUND 8

#define COLLISION_BIT_BLOBBY  1 // 0000 0000 0000 0001
#define COLLISION_BIT_GROUND  2 // 0000 0000 0000 0010
#define COLLISION_BIT_WEAPON  4 // 0000 0000 0000 0100
#define COLLISION_BIT_OBJECT  8 // 0000 0000 0000 1000
#define COLLISION_BIT_BULLET 16 // 0000 0000 0001 0000
#define COLLISION_BIT_PLAYER 32 // 0000 0000 0001 0000

class IEntity
{
public:
	virtual void draw() = 0;
	virtual void destroy() = 0;
	virtual void addBody(b2Body *body) = 0;
	virtual b2Body* getBody(unsigned int i) = 0;
	virtual unsigned int getBodyCount() = 0;
};

#endif