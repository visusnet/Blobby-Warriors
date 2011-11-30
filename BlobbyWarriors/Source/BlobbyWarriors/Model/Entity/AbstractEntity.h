#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

#include <vector>

#include <GL/glut.h>
#include <Box2D.h>

#include "../PhysicsUtils.h"
#include "IEntity.h"
#include "../../Debug.h"
#include "../../UI/Graphics/TextureManager.h"

using namespace std;

#define DIRECTION_UNKNOWN 0
#define DIRECTION_LEFT 1
#define DIRECTION_RIGHT 2

class AbstractEntity : public IEntity
{
public:
	AbstractEntity();
	virtual void step();
	virtual void draw();
	void destroy();
	void addBody(b2Body *body);
	b2Body* getBody(unsigned int i);
	unsigned int getBodyCount();
	void addTexture(Texture *texture);
	Texture* getTexture(unsigned int i);
	unsigned int getTextureCount();
	void setViewingDirection(int viewingDirection);
	int getViewingDirection();
protected:
	vector<b2Body*> bodies;
	vector<Texture*> textures;
private:
	bool isDestroyed;
	int viewingDirection;
};

#include "../GameWorld.h"

#endif