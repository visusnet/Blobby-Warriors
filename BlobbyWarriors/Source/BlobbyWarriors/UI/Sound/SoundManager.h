#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <list>

#include "Sound.h"

using namespace std;

class SoundManager
{
public:
	static SoundManager* getInstance();
	Sound* loadSound(char *filename);
private:
	SoundManager();
	SoundManager(const SoundManager&);
	~SoundManager();

	static SoundManager *instance;

	list<Sound*> sounds;

	class Guard
	{
	public:
		~Guard()
		{
			if (SoundManager::instance != 0) {
				delete SoundManager::instance;
			}
		}
	};
	friend class Guard;
};


#endif