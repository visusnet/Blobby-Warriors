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

Camera::Camera()
{
	this->reset();
}

Camera::~Camera()
{
}

Camera *Camera::instance = 0;