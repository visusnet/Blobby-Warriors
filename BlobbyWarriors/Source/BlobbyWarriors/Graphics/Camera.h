#ifndef CAMERA_H
#define CAMERA_H

#include <GL/glut.h>

#include <Box2D.h>

#include "../PublishSubscribe.h"
#include "../Debug.h"

class CameraEventArgs : public UpdateData
{
};

struct Size
{
	int width;
	int height;
};

class Camera : public Publisher
{
public:
	static Camera* getInstance();
	void setViewCenter(b2Vec2 viewCenter);
	b2Vec2 getViewCenter();
	void setZoom(float zoom);
	float getZoom();
	void setWindowPosition(int x, int y);
	b2Vec2 getWindowPosition();
	void setWindowSize(int width, int height);
	Size getWindowSize();
	void reset();

	void operator+=(const b2Vec2& vector);
	void operator-=(const b2Vec2& vector);
	void operator*=(const float& factor);
	void operator/=(const float& factor);

	static b2Vec2 convertWorldToScreen(float x, float y);
	static b2Vec2 convertScreenToWorld(int x, int y);
private:
	Camera();
	Camera(const Camera&);
	~Camera();

	b2Vec2 viewCenter;
	float zoom;
	b2Vec2 windowPosition;
	Size windowSize;

	static Camera *instance;

	class Guard
	{
	public:
		~Guard()
		{
			if (Camera::instance != 0) {
				delete Camera::instance;
			}
		}
	};
	friend class Guard;
};

#endif