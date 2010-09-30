#pragma once

#include <Box2D.h>

#include "GraphicsEngine.h"

class GameObject
{
	friend class GameObjectCreator;
public:
	GameObject();
	virtual ~GameObject(void) = 0;
	b2Body* GetBody();
	float GetPositionX();
	float GetPositionY();
protected:
	void SetBody(b2Body *body);
private:
	b2Body *body;
};
