#include "SoundEngine.h"

SoundEngine* SoundEngine::getInstance()
{
	static Guard guard;
	if(SoundEngine::instance == 0) {
		SoundEngine::instance = new SoundEngine();
	}
	return SoundEngine::instance;
}

void SoundEngine::play(Sound *sound)
{
	if (!this->engine) {
		debug("Sound engine is not started. Could not play sound.");
	}

	this->engine->play2D(sound->filename, sound->loop);
}

SoundEngine::SoundEngine()
{
	this->engine = createIrrKlangDevice();

	if (!this->engine) {
		debug("Could not start sound engine.");
	}
}

SoundEngine::~SoundEngine()
{
}

SoundEngine* SoundEngine::instance = 0;
