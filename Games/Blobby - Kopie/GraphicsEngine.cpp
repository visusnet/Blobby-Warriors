#include "GraphicsEngine.h"

void Timer(int)
{
	glutSetWindow(mainWindow);
	glutPostRedisplay();
	glutTimerFunc(16, Timer, 0);
}

GraphicsEngine::GraphicsEngine(int argc, char **argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	mainWindow = glutCreateWindow("Blobby Warriors");

	glutTimerFunc(16, Timer, 0);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(0, width, 0, height);
	glMatrixMode(GL_MODELVIEW);
}

GraphicsEngine::~GraphicsEngine(void)
{
}

void GraphicsEngine::SetResizeCallback(void (callback)(int, int))
{
	glutReshapeFunc(callback);
}

void GraphicsEngine::SetKeyboardCallback(void (callback)(unsigned char, int, int))
{
	glutKeyboardFunc(callback);
}

void GraphicsEngine::SetMouseCallback(void (callback)(int, int, int, int))
{
	glutMouseFunc(callback);
}

void GraphicsEngine::SetDrawCallback(void (callback)(void))
{
	glutDisplayFunc(callback);
}

void GraphicsEngine::SetIdleCallback(void (callback)(void))
{
	glutIdleFunc(callback);
}

void GraphicsEngine::MainLoop()
{
	glutMainLoop();
}

void GraphicsEngine::DrawRectangle(float x, float y, float w, float h, float angle)
{
	B2_NOT_USED(x);
	B2_NOT_USED(y);
	B2_NOT_USED(w);
	B2_NOT_USED(h);
	B2_NOT_USED(angle);

/*	glMatrixMode(GL_MODELVIEW);
	glRotatef(angle, 0.0, 1.0, 0.0);
	glBegin(GL_POLYGON);
//		glVertex2f(x - w / 2, y - h / 2);
//		glVertex2f(x + w / 2, y - h / 2);
//		glVertex2f(x + w / 2, y + h / 2);
//		glVertex2f(x - w / 2, y + h / 2);
		glVertex2f(x, y);
		glVertex2f(x + w, y);
		glVertex2f(x + w, y - h);
		glVertex2f(x, y - h);
	glEnd();*/
}

void GraphicsEngine::ClearScreen()
{
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

/*	glClear(GL_COLOR_BUFFER_BIT);
	glColor3f(1.0, 1.0, 1.0);*/
}

void GraphicsEngine::Flush()
{
	glutSwapBuffers();
//	glFlush();
//	glutSwapBuffers();
}