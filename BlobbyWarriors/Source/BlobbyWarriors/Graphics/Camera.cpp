#include "Camera.h"

Camera* Camera::getInstance()
{
	static Guard guard;
	if(Camera::instance == 0) {
		Camera::instance = new Camera();
	}
	return Camera::instance;
}

void Camera::setViewCenter(b2Vec2 viewCenter)
{
	this->viewCenter = viewCenter;
	this->notify(new CameraEventArgs());
}

b2Vec2 Camera::getViewCenter()	
{
	return this->viewCenter;
}

void Camera::setZoom(float zoom)	
{
	this->zoom = zoom;
	this->notify(new CameraEventArgs());
}

float Camera::getZoom()
{
	return this->zoom;
}

void Camera::setWindowPosition(int x, int y)
{
	this->windowPosition.Set(x, y);
}

b2Vec2 Camera::getWindowPosition()
{
	return this->windowPosition;
}

void Camera::setWindowSize(int width, int height)
{
	this->windowSize.width = width;
	this->windowSize.height = height;
}

Size Camera::getWindowSize()
{
	return this->windowSize;
}

void Camera::reset()
{
	this->viewCenter = b2Vec2(400.0f, 300.0f);
	this->zoom = 1.0f;
}

void Camera::operator+=(const b2Vec2& vector)
{
	this->viewCenter += vector;
}

void Camera::operator-=(const b2Vec2& vector)
{
	this->viewCenter -= vector;
}

void Camera::operator*=(const float& factor)
{
	this->zoom *= factor;
}

void Camera::operator/=(const float& factor)
{
	this->zoom /= factor;
}

b2Vec2 Camera::convertWorldToScreen(float x, float y)
{
/*	static GLint viewport[4];
	static GLdouble modelview[16];
	static GLdouble projection[16];
	static GLfloat winX, winY, winZ;
	double worldX, worldY, worldZ;

	glGetDoublev(GL_MODELVIEW_MATRIX, modelview);
	glGetDoublev(GL_PROJECTION_MATRIX, projection);
	glGetIntegerv(GL_VIEWPORT, viewport);

	winX = (GLfloat)x;
	winY = (GLfloat)y;
	winZ = (GLfloat)0;

	gluProject(winX, winY, winZ, modelview, projection, viewport, &worldX, &worldY, &worldZ);

	return b2Vec2((GLfloat)worldX, (GLfloat)viewport[3] - (GLfloat)worldY);*/

	Size windowSize = Camera::getInstance()->getWindowSize();
	b2Vec2 viewCenter = Camera::getInstance()->getViewCenter();

	b2Vec2 extents(windowSize.width / 2.0f, windowSize.height / 2.0f);
	extents *= Camera::getInstance()->getZoom();

	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	float u = (x - lower.x) / (upper.x - lower.x);
	float v = (y - lower.y) / (upper.y - lower.y);

	b2Vec2 p;
	p.x = u * windowSize.width;
	p.y = windowSize.height - v * windowSize.height;

	return p;
}

b2Vec2 Camera::convertScreenToWorld(int x, int y)
{
	Size windowSize = Camera::getInstance()->getWindowSize();
	b2Vec2 viewCenter = Camera::getInstance()->getViewCenter();

	float u = float(x) / windowSize.width;
	float v = float(windowSize.height - y) / windowSize.height;

	b2Vec2 extents(windowSize.width / 2.0f, windowSize.height / 2.0f);
	extents *= Camera::getInstance()->getZoom();

	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	b2Vec2 p;
	p.x = (1.0f - u) * lower.x + u * upper.x;
	p.y = (1.0f - v) * lower.y + v * upper.y;

	return p;
}

Camera::Camera()
{
	this->reset();
}

Camera::~Camera()
{
}

Camera *Camera::instance = 0;