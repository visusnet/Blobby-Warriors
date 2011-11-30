#include "SoundManager.h"

SoundManager* SoundManager::getInstance()
{
	static Guard guard;
	if (SoundManager::instance == 0) {
		SoundManager::instance = new SoundManager();
	}
	return SoundManager::instance;
}

ISoundEngine* SoundManager::getEngine()
{
	return this->engine;
}

SoundManager::SoundManager()
{
	this->engine = createIrrKlangDevice();

	if (!this->engine) {
		debug("Could not start sound engine.");
	}
}

SoundManager::~SoundManager()
{
}

SoundManager* SoundManager::instance = 0;
