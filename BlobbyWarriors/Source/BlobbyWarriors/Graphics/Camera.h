#ifndef CAMERA_H
#define CAMERA_H

#include <Box2D.h>

#include "../PublishSubscribe.h"

class CameraEventArgs : public UpdateData
{
};

class Camera : public Publisher
{
public:
	static Camera* getInstance();
	void setViewCenter(b2Vec2 viewCenter);
	b2Vec2 getViewCenter();
	void setZoom(float zoom);
	float getZoom();
	void reset();

	void operator+=(const b2Vec2& vector);
	void operator-=(const b2Vec2& vector);
	void operator*=(const float& factor);
	void operator/=(const float& factor);
private:
	Camera();
	Camera(const Camera&);
	~Camera();

	b2Vec2 viewCenter;
	float zoom;

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