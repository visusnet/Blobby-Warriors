#ifndef SOUNDENGINE_H
#define SOUNDENGINE_H

#include <irrklang.h>
#include <iostream>

#include "Sound.h"
#include "SoundManager.h"
#include "../../Debug.h"

using namespace irrklang;

class SoundEngine
{
public:
	static SoundEngine* getInstance();
	void play(Sound* sound);
private:
	SoundEngine();
	SoundEngine(const SoundEngine&);
	~SoundEngine();

	static SoundEngine *instance;

	ISoundEngine* engine;

	class Guard
	{
	public:
		~Guard()
		{
			if (SoundEngine::instance != 0) {
				delete SoundEngine::instance;
			}
		}
	};
	friend class Guard;
};

#endif