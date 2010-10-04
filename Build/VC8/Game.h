#ifndef GAME_H
#define GAME_H

#include <stdio.h>

#include "Render.h"
#include "Texturizer.h"
#include "Box2D.h"
#include "glui/GL/glui.h"

class Game;
struct Settings;

#include "DestructionListener.h"
#include "BoundaryListener.h"
#include "ContactListener.h"
#include "Settings.h"

#include "KeyEventHandler.h"

#include "Blobby.h"

class Game
{
public:
	Game();
	~Game();
	void Step(Settings* settings);
	void InitializeLevel();
	Blobby* CreateBlobby();
	Blobby* playerBlobby;

protected:
	friend class DestructionListener;
	friend class BoundaryListener;
	friend class ContactListener;

	b2AABB m_worldAABB;
	ContactPoint m_points[k_maxContactPoints];
	int32 m_pointCount;
	DestructionListener m_destructionListener;
	BoundaryListener m_boundaryListener;
	ContactListener m_contactListener;
	Render m_debugDraw;
	int32 m_textLine;
	b2World* m_world;
	b2Body* m_bomb;
	b2MouseJoint* m_mouseJoint;
};

namespace
{
	float scalingFactor = 15;
	Settings settings;
	int32 width = 800;
	int32 height = 600;
	int32 framePeriod = 16;
	int32 mainWindow;
	float settingsHz = 60.0;
	GLUI *glui;
	float32 viewZoom = 1.0;
	b2Vec2 viewCenter(0.0f, 20.0f);
	int tx, ty, tw, th;
	bool rMouseDown;
	b2Vec2 lastp;
	Game *game;
	KeyEventHandler *keyEventHandler;
	KeyList *keyList;
	int updatePrevious;
	Texturizer *texturizer;
}


#endif
