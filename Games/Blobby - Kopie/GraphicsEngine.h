#pragma once

#include "Globals.h"

class GraphicsEngine
{
public:
	GraphicsEngine(int argc, char **argv);
	~GraphicsEngine(void);
	void SetResizeCallback(void (callback)(int, int));
	void SetKeyboardCallback(void (callback)(unsigned char, int, int));
	void SetMouseCallback(void (callback)(int, int, int, int));
	void SetDrawCallback(void (callback)());
	void SetIdleCallback(void (callback)());
	void MainLoop();
	static void DrawRectangle(float x, float y, float w, float h, float angle);
	static void ClearScreen();
	static void Flush();
};
