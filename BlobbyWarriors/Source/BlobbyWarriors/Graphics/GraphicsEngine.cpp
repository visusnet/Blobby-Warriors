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

	Camera::getInstance()->subscribe(this);
}

void GraphicsEngine::start()
{
	// Start the main loop.
	glutMainLoop();
}

void GraphicsEngine::update(Publisher *who, UpdateData *what)
{
	CameraEventArgs *cameraEventArgs = dynamic_cast<CameraEventArgs*>(what);
	if (cameraEventArgs != 0) {
		this->onReshape();
	}

//	debug("YES %d %d", eventArgs->x, eventArgs->y);

/*	switch(eventArgs->type) {
	case MOUSE_BUTTON_STATE_CHANGED:
	case MOUSE_POSITION_CHANGED:
		this->viewCenter = b2Vec2(float(this->windowInfo.width - eventArgs->x), float(eventArgs->y));
		this->onReshape();
		break;
	}*/
}

void GraphicsEngine::drawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
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
	Camera::getInstance()->setWindowSize(width, height);
	GraphicsEngine::getInstance()->onReshape();
}

GraphicsEngine::GraphicsEngine()
{
	this->mainWindow = 0;
	this->isFullScreen = false;
	Camera::getInstance()->setWindowSize(WIDTH, HEIGHT);
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);
}

GraphicsEngine::~GraphicsEngine()
{
}

void GraphicsEngine::onKeyDown(unsigned char key, int x, int y)
{
//	debug("%c %i %i", key, x, y);

	KeyboardHandler::getInstance()->setKeyDown(key);

	switch (key)
	{
	case 'q':
		exit(0);
		break;
	case 'f':
		this->isFullScreen = !this->isFullScreen;
		if (this->isFullScreen) {
			Camera::getInstance()->setWindowPosition(glutGet(GLUT_WINDOW_X), glutGet(GLUT_WINDOW_Y));
			Camera::getInstance()->setWindowSize(glutGet(GLUT_WINDOW_WIDTH), glutGet(GLUT_WINDOW_HEIGHT));
			glutFullScreen();
		} else {
			// Switch into windowed mode and repostion top-left corner.
			glutReshapeWindow(Camera::getInstance()->getWindowSize().width, Camera::getInstance()->getWindowSize().height);
			glutPositionWindow(int(Camera::getInstance()->getWindowPosition().x), int(Camera::getInstance()->getWindowPosition().y));
		}
		glutFullScreen();
		this->onReshape();
		break;
	}
}

void GraphicsEngine::onKeyUp(unsigned char key, int x, int y)
{
//	debug("%c %i %i", key, x, y);
	
	KeyboardHandler::getInstance()->setKeyUp(key);
}

void GraphicsEngine::onSpecialKeyDown(int key, int x, int y)
{
//	debug("%i %i %i", key, x, y);

	KeyboardHandler::getInstance()->setKeyDown(static_cast<unsigned char>(key));

	switch (key)
	{
	case GLUT_KEY_LEFT:
		(*Camera::getInstance()) -= b2Vec2(0, 0);
		this->onReshape();
		break;

	case GLUT_KEY_RIGHT:
		(*Camera::getInstance()) += b2Vec2(0.5f, 0.0f);
		this->onReshape();
		break;

	case GLUT_KEY_DOWN:
		(*Camera::getInstance()) -= b2Vec2(0.0f, 0.5f);
		this->onReshape();
		break;

	case GLUT_KEY_UP:
		(*Camera::getInstance()) += b2Vec2(0.0f, 0.5f);
		this->onReshape();
		break;

	case GLUT_KEY_HOME:
		Camera::getInstance()->reset();
		this->onReshape();
		break;
	}
}

void GraphicsEngine::onSpecialKeyUp(int key, int x, int y)
{
//	debug("%i %i %i", key, x, y);

	KeyboardHandler::getInstance()->setKeyUp(static_cast<unsigned char>(key));
}

void GraphicsEngine::onMouseButton(int button, int state, int x, int y)
{
//	debug("%i %i %i %i", button, state, x, y);	

	b2Vec2 position = Camera::convertScreenToWorld(x, y);
	MouseHandler::getInstance()->onMouseButton(button, state, x, y);
}

void GraphicsEngine::onMouseWheel(int wheel, int direction, int x, int y)
{
//	debug("%i %i %i %i", wheel, direction, x, y);

	if (direction > 0)
	{
		(*Camera::getInstance()) /= 1.1f;
	}
	else
	{
		(*Camera::getInstance()) *= 1.1f;
	}
	debug("%f", Camera::getInstance()->getZoom());
	this->onReshape();
}

void GraphicsEngine::onMouseMotion(int x, int y)
{
	//debug("%i %i", x, y);
}

void GraphicsEngine::onMousePassiveMotion(int x, int y)
{
	//debug("%i %i", x, y);
}

void GraphicsEngine::onMouseMove(int x, int y)
{
//	debug("%i %i", x, y);

	MouseHandler::getInstance()->onMouseMove(x, y);
}

// TODO: Remove me! This is just for debugging purposes
inline void drawPolygonAt(int x, int y)
{
	glColor3f(1.0f, 1.0f, 1.0f);
	glBegin(GL_POLYGON);
		glVertex3f(x +  0.0f, y +  0.0f, 0.0f);
		glVertex3f(x + 10.0f, y +  0.0f, 0.0f);
		glVertex3f(x + 10.0f, y + 10.0f, 0.0f);
		glVertex3f(x +  0.0f, y + 10.0f, 0.0f);
	glEnd();
}

void GraphicsEngine::onDraw()
{
	float fps = 1000.0f / (glutGet(GLUT_ELAPSED_TIME) - this->previousTicks);
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	drawString(610, 40, "FPS:       %f", fps);
	drawString(610, 55, "Bodies:    %i", GameWorld::getInstance()->getPhysicsWorld()->GetBodyCount());
	drawString(610, 70, "Entities:  %i", GameWorld::getInstance()->getEntityCount());

	// TODO: Draw everything
	drawPolygonAt(0, 0);
	drawPolygonAt(790, 590);
	drawPolygonAt(0, 590);
	drawPolygonAt(790, 0);
	drawPolygonAt(395, 295);

	this->notify();

	drawString(610, 85, "Gen. Time: %i ms", glutGet(GLUT_ELAPSED_TIME) - this->previousTicks);

	glutSwapBuffers();
}

void GraphicsEngine::onTimerTick()
{
	glutSetWindow(this->mainWindow);
	glutPostRedisplay();
	glutTimerFunc(FRAME_PERIOD, onTimerTickCallback, 0);
}

void GraphicsEngine::onReshape()
{
	Size windowSize = Camera::getInstance()->getWindowSize();
	b2Vec2 viewCenter = Camera::getInstance()->getViewCenter();

	glViewport(0, 0, int(windowSize.width), int(windowSize.height));
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();

	b2Vec2 extents(windowSize.width / 2.0f, windowSize.height / 2.0f);
	extents *= Camera::getInstance()->getZoom();
	
	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

GraphicsEngine *GraphicsEngine::instance = 0;