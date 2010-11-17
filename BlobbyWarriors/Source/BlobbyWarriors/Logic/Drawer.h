#ifndef DRAWER_H
#define DRAWER_H

#include "../Model/GameWorld.h"

class Drawer
{
public:
	static Drawer* getInstance();
	void draw();
private:
	Drawer();
	Drawer(const Drawer&);
	~Drawer();

	static Drawer *instance;

	Texture *texture;
	
	class Guard
	{
	public:
		~Guard()
		{
			if (Drawer::instance != 0) {
				delete Drawer::instance;
			}
		}
	};
	friend class Guard;
};

#endif