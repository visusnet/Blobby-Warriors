#ifndef ABSTRACTENTITY_H
#define ABSTRACTENTITY_H

class AbstractEntity;

#include <vector>

#include <GL/glut.h>
#include <Box2D.h>

#include "../GameWorld.h"
#include "../PhysicsUtils.h"
#include "IEntity.h"
#include "../../Debug.h"
#include "../../UI/Graphics/TextureManager.h"

using namespace std;

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
protected:
	vector<b2Body*> bodies;
	vector<Texture*> textures;
private:
	bool isDestroyed;
};

#endif