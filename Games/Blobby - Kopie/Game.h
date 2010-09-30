#pragma once

#include <iostream>

#include "glui/GL/glui.h"

#include "World.h"
#include "GraphicsEngine.h"
#include "KeyEventHandler.h"
#include "KeyList.h"
#include "Player.h"

using namespace std;

class Game
{
public:
	Game(void);
	~Game(void);
};

void ResizeCallback(int w, int h);
void KeyEventDown(unsigned int key);
void KeyEventUp(unsigned int key);
void Update(KeyList *keyList);
