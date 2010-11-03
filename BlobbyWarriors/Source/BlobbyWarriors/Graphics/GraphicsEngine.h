#ifndef _GRAPHICSENGINE_H
#define _GRAPHICSENGINE_H

#include <GL/glut.h>

#include <Box2D.h>

#include "../Debug.h"
#include "../PublishSubscribe.h"
#include "Camera.h"
#include "KeyboardHandler.h"
#include "MouseHandler.h"
#include "../Model/GameWorld.h"

class GraphicsEngine : public Publisher, public Subscriber
{
public:
	static GraphicsEngine* getInstance();

	void initialize(int argc, char **argv);
	void start();
	void update(Publisher *who, UpdateData *what = 0);

	static void drawString(int x, int y, const char *string, ...);
	static void onKeyDownCallback(unsigned char key, int x, int y);
	static void onKeyUpCallback(unsigned char key, int x, int y);
	static void onSpecialKeyDownCallback(int key, int x, int y);
	static void onSpecialKeyUpCallback(int key, int x, int y);
	static void onMouseButtonCallback(int button, int state, int x, int y);
	static void onMouseWheelCallback(int wheel, int direction, int x, int y);
	static void onMouseMotionCallback(int x, int y);
	static void onMousePassiveMotionCallback(int x, int y);
	static void onDrawCallback();
	static void onTimerTickCallback(int);
	static void onReshapeCallback(int width, int height);
private:
	GraphicsEngine();
	GraphicsEngine(const GraphicsEngine&);
	~GraphicsEngine();

	void onKeyDown(unsigned char key, int x, int y);
	void onKeyUp(unsigned char key, int x, int y);
	void onSpecialKeyDown(int key, int x, int y);
	void onSpecialKeyUp(int key, int x, int y);
	void onMouseButton(int button, int state, int x, int y);
	void onMouseWheel(int wheel, int direction, int x, int y);
	void onMouseMotion(int x, int y);
	void onMousePassiveMotion(int x, int y);
	void onMouseMove(int x, int y);
	void onDraw();
	void onTimerTick();
	void onReshape();

	static GraphicsEngine *instance;

	int mainWindow;
	bool isFullScreen;
	int previousTicks;

	class Guard
	{
	public:
		~Guard()
		{
			if (GraphicsEngine::instance != 0) {
				delete GraphicsEngine::instance;
			}
		}
	};
	friend class Guard;
};

#endif