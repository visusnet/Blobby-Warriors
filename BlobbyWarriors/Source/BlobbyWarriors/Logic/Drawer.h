#ifndef DRAWER_H
#define DRAWER_H

class Drawer;

#include "../Model/GameWorld.h"

class Drawer
{
public:
	static Drawer* getInstance();
	void draw();

	static void drawString(int x, int y, const char *string, ...);
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