#pragma once

#include <Box2D.h>

#ifdef __APPLE__
#include <GLUT/glut.h>
#else
#include "freeglut/GL/glut.h"
#endif

#include "glui/GL/glui.h"

#include "KeyEventHandler.h"
#include "KeyList.h"

#define SCALING_FACTOR 30.0f

namespace
{
	int width = 800;
	int height = 600;
	int framePeriod = 16;
	int mainWindow;
	float settingsHz = 60.0;
	GLUI *glui;
	float viewZoom = 1.0f;
	b2Vec2 viewCenter(0.0f, 0.0f);
	int tx, ty, tw, th;
	KeyEventHandler *keyEventHandler;
	KeyList *keyList;
}
