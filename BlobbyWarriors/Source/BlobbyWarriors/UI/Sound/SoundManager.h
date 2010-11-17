#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <irrklang.h>
#include <iostream>

#include "../../Debug.h"

using namespace irrklang;

class SoundManager
{
public:
	static SoundManager* getInstance();
	ISoundEngine* getEngine();
private:
	SoundManager();
	SoundManager(const SoundManager&);
	~SoundManager();

	ISoundEngine *engine;

	static SoundManager *instance;

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