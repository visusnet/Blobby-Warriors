#include "SoundManager.h"

SoundManager* SoundManager::getInstance()
{
	static Guard guard;
	if(SoundManager::instance == 0) {
		SoundManager::instance = new SoundManager();
	}
	return SoundManager::instance;
}

Sound* SoundManager::loadSound(char *filename)
{
	for (list<Sound*>::iterator it = this->sounds.begin(); it != this->sounds.end(); ++it) {
		Sound *sound = *it;
		if (strncmp(sound->filename, filename, sizeof(sound->filename)) == 0) {
			return sound;
		}
	}
	Sound *sound = new Sound();
	sound->filename = filename;
	sound->loop = false; // for now...
	this->sounds.push_back(sound);
	return sound;
}

SoundManager::SoundManager()
{
}

SoundManager::~SoundManager()
{
}

SoundManager* SoundManager::instance = 0;
