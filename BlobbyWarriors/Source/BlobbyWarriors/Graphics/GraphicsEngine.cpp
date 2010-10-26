#include "GraphicsEngine.h"

// TODO: Remove the constants
#define WIDTH 800
#define HEIGHT 600
#define TITLE "Blobby Warriors"
#define FRAME_PERIOD 16 // 1 / 0,016 ms = 62,5 Hz

GraphicsEngine* GraphicsEngine::getInstance()
{
	static Guard guard;
	if(GraphicsEngine::instance == 0) {
		GraphicsEngine::instance = new GraphicsEngine();
	}
	return GraphicsEngine::instance;
}

void GraphicsEngine::initialize(int argc, char **argv)
{
	// Initialize the window.
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(WIDTH, HEIGHT);
	
	// Create the window.
	this->mainWindow = glutCreateWindow(TITLE);

	// Set keyboard methods.
	glutKeyboardFunc(&onKeyDownCallback);
	glutKeyboardUpFunc(&onKeyUpCallback);
	glutSpecialFunc(&onSpecialKeyDownCallback);
	glutSpecialUpFunc(&onSpecialKeyUpCallback);

	// Set mouse callbacks.
	glutMouseFunc(&onMouseButtonCallback);
#ifdef FREEGLUT
	glutMouseWheelFunc(&onMouseWheelCallback);
#endif
	glutMotionFunc(&onMouseMotionCallback);
	glutPassiveMotionFunc(&onMousePassiveMotionCallback);

	// Set display callbacks.
	glutDisplayFunc(&onDrawCallback);
	glutReshapeFunc(&onReshapeCallback);

	// Set a timer to control the frame rate.
	glutTimerFunc(FRAME_PERIOD, onTimerTickCallback, 0);

	//glutFullScreen();
	//glutGameModeString("800x600:16@60");
}

void GraphicsEngine::start()
{
	// Start the main loop.
	glutMainLoop();
}

void GraphicsEngine::onKeyDownCallback(unsigned char key, int x, int y)
{
	GraphicsEngine::getInstance()->onKeyDown(key, x, y);
}

void GraphicsEngine::onKeyUpCallback(unsigned char key, int x, int y)
{
	GraphicsEngine::getInstance()->onKeyUp(key, x, y);
}

void GraphicsEngine::onSpecialKeyDownCallback(int key, int x, int y)
{
	GraphicsEngine::getInstance()->onSpecialKeyDown(key, x, y);
}

void GraphicsEngine::onSpecialKeyUpCallback(int key, int x, int y)
{
	GraphicsEngine::getInstance()->onSpecialKeyUp(key, x, y);
}

void GraphicsEngine::onMouseButtonCallback(int button, int state, int x, int y)
{
	GraphicsEngine::getInstance()->onMouseButton(button, state, x, y);
}

void GraphicsEngine::onMouseWheelCallback(int wheel, int direction, int x, int y)
{
	GraphicsEngine::getInstance()->onMouseWheel(wheel, direction, x, y);
}

void GraphicsEngine::onMouseMotionCallback(int x, int y)
{
	GraphicsEngine::getInstance()->onMouseMotion(x, y);
	GraphicsEngine::getInstance()->onMouseMove(x, y);
}

void GraphicsEngine::onMousePassiveMotionCallback(int x, int y)
{
	GraphicsEngine::getInstance()->onMousePassiveMotion(x, y);
	GraphicsEngine::getInstance()->onMouseMove(x, y);
}

void GraphicsEngine::onDrawCallback()
{
	GraphicsEngine::getInstance()->onDraw();
}

void GraphicsEngine::onTimerTickCallback(int)
{
	GraphicsEngine::getInstance()->onTimerTick();
}

void GraphicsEngine::onReshapeCallback(int width, int height)
{
	GraphicsEngine::getInstance()->onReshape(width, height);
}

GraphicsEngine::GraphicsEngine()
{
	this->mainWindow = 0;
	this->viewZoom = 1.0f;
	this->viewCenter = b2Vec2(0.0f, 20.0f);
	this->isFullScreen = false;
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::onKeyDown(unsigned char key, int x, int y)
{
	debug("%c %i %i", key, x, y);

	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'f':
		this->isFullScreen = !this->isFullScreen;
		if (this->isFullScreen) {
			this->windowInfo.x = glutGet(GLUT_WINDOW_X);
			this->windowInfo.y = glutGet(GLUT_WINDOW_Y);
			this->windowInfo.width = glutGet(GLUT_WINDOW_WIDTH);
			this->windowInfo.height = glutGet(GLUT_WINDOW_HEIGHT);
			glutFullScreen();
		} else {
			// Switch into windowed mode and repostion top-left corner.
			glutReshapeWindow(WIDTH, HEIGHT);
//			glutReshapeWindow(this->windowInfo.width, this->windowInfo.height);
			glutPositionWindow(this->windowInfo.x, this->windowInfo.y);
		}
		glutFullScreen();
		this->onReshape(WIDTH, HEIGHT);
		break;
	}
}

void GraphicsEngine::onKeyUp(unsigned char key, int x, int y)
{
	debug("%c %i %i", key, x, y);
}

void GraphicsEngine::onSpecialKeyDown(int key, int x, int y)
{
	debug("%i %i %i", key, x, y);

	switch (key)
	{
	case GLUT_ACTIVE_SHIFT:
	case GLUT_KEY_LEFT:
		this->viewCenter.x -= 0.5f;
		this->onReshape(WIDTH, HEIGHT);
		break;

	case GLUT_KEY_RIGHT:
		this->viewCenter.x += 0.5f;
		this->onReshape(WIDTH, HEIGHT);
		break;

	case GLUT_KEY_DOWN:
		this->viewCenter.y -= 0.5f;
		this->onReshape(WIDTH, HEIGHT);
		break;

	case GLUT_KEY_UP:
		this->viewCenter.y += 0.5f;
		this->onReshape(WIDTH, HEIGHT);
		break;

	case GLUT_KEY_HOME:
		this->viewZoom = 1.0f;
		this->viewCenter.Set(0.0f, 20.0f);
		this->onReshape(WIDTH, HEIGHT);
		break;
	}
}

void GraphicsEngine::onSpecialKeyUp(int key, int x, int y)
{
	debug("%i %i %i", key, x, y);
}

void GraphicsEngine::onMouseButton(int button, int state, int x, int y)
{
	debug("%i %i %i %i", button, state, x, y);
}

void GraphicsEngine::onMouseWheel(int wheel, int direction, int x, int y)
{
	debug("%i %i %i %i", wheel, direction, x, y);

	if (direction > 0)
	{
		viewZoom /= 1.1f;
	}
	else
	{
		viewZoom *= 1.1f;
	}
	debug("%f", viewZoom);
	this->onReshape(WIDTH, HEIGHT);
}

void GraphicsEngine::onMouseMotion(int x, int y)
{
	debug("%i %i", x, y);
}

void GraphicsEngine::onMousePassiveMotion(int x, int y)
{
	debug("%i %i", x, y);
}

void GraphicsEngine::onMouseMove(int x, int y)
{
	debug("%i %i", x, y);
}

void GraphicsEngine::onDraw()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	// TODO: Draw everything
	glBegin(GL_TRIANGLES);
		glVertex3f( 0.0f, 1.0f, 0.0f);
		glVertex3f(-1.0f,-1.0f, 0.0f);
		glVertex3f( 1.0f,-1.0f, 0.0f);
	glEnd();

	glutSwapBuffers();
}

void GraphicsEngine::onTimerTick()
{
	glutSetWindow(this->mainWindow);
	glutPostRedisplay();
	glutTimerFunc(FRAME_PERIOD, onTimerTickCallback, 0);
}

void GraphicsEngine::onReshape(int width, int height)
{
	glViewport(0, 0, width, height);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	float ratio = float32(width) / float32(height);

	b2Vec2 extents(ratio * 25.0f, 25.0f);
	extents *= this->viewZoom;

	b2Vec2 lower = this->viewCenter - extents;
	b2Vec2 upper = this->viewCenter + extents;

	gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

GraphicsEngine *GraphicsEngine::instance = 0;