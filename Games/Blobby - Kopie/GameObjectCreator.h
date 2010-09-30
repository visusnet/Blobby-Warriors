#pragma once

#include <vector>

using namespace std;

#include <Box2D.h>

#include "Globals.h"
#include "GameObject.h"

#define PI 3.14159265358979323846f

struct GameObjectSettings
{
	vector<b2Vec2*> vertices;
	float density;
	float friction;
	float restitution;
	float x;
	float y;
	float angle;
	float radius;

	void SetAngleInDegrees(float radians)
	{
		this->angle = radians * 180 / PI;
	}
};

class GameObjectCreator
{
public:
	GameObjectCreator() { }
	GameObject* CreateObject(GameObjectSettings settings);
	GameObject* CreateObject();
	virtual GameObjectSettings GetDefaultSettings() = 0;
	virtual int GetObjectCount() = 0;
protected:
	virtual GameObject* Create(GameObjectSettings settings) = 0;
};

#include "World.h"