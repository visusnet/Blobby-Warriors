#include "AbstractWeapon.h"

AbstractWeapon::AbstractWeapon()
{
	this->isActive = false;
	this->soundSources[WEAPON_EVENT_FIRE] = 0;
	this->soundSources[WEAPON_EVENT_STOP_FIRE] = 0;
	this->sounds[WEAPON_EVENT_FIRE] = 0;
	this->sounds[WEAPON_EVENT_STOP_FIRE] = 0;
	this->soundSingelton[WEAPON_EVENT_FIRE] = true;
	this->soundSingelton[WEAPON_EVENT_STOP_FIRE] = true;
}

void AbstractWeapon::fire(b2Vec2 direction, bool constantFire, bool isPlayer)
{
	if (hasSoundSource(WEAPON_EVENT_FIRE) && (!this->soundSingelton[WEAPON_EVENT_FIRE] || !isSoundPlaying(WEAPON_EVENT_FIRE))) {
		debug("play start fire");
		this->sounds[WEAPON_EVENT_FIRE] = SoundManager::getInstance()->getEngine()->play2D(this->soundSources[WEAPON_EVENT_FIRE], true, false, true);
		debug("sound is %s", this->sounds[WEAPON_EVENT_FIRE] == 0 ? "null" : "not null");
	}
	this->onFire(direction, constantFire, isPlayer);
}

void AbstractWeapon::stopFire()
{
	if (hasSoundSource(WEAPON_EVENT_FIRE) && isSoundPlaying(WEAPON_EVENT_FIRE)) {
		debug("jo");
		this->sounds[WEAPON_EVENT_FIRE]->stop();
		this->sounds[WEAPON_EVENT_FIRE] = 0;
	}
	if (hasSoundSource(WEAPON_EVENT_STOP_FIRE)) {
		debug("play stop fire");
		this->sounds[WEAPON_EVENT_STOP_FIRE] = SoundManager::getInstance()->getEngine()->play2D(this->soundSources[WEAPON_EVENT_STOP_FIRE], true, false, true);
	}
	this->onStopFire();
}

void AbstractWeapon::onStopFire()
{
}

void AbstractWeapon::draw()
{
	if (this->isActive)
	{
		if (this->getViewingDirection()==DIRECTION_LEFT)
		{
			Texturizer::draw(this->getTexture(0), this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, degree2radian(radian2degree(this->getBody(0)->GetAngle()) + 180), 40, 19);
		}
		else
		{
			Texturizer::draw(this->getTexture(0), this->getBody(0)->GetPosition().x, this->getBody(0)->GetPosition().y, degree2radian(radian2degree(this->getBody(0)->GetAngle()) + 180), 40, 19, true, false, 0, 0);
		}
	}
	//	AbstractEntity::draw();
}

void AbstractWeapon::setActive(bool isActive)
{
	this->isActive = isActive;
	if (hasSoundSource(WEAPON_EVENT_FIRE) && isSoundPlaying(WEAPON_EVENT_FIRE)) {
		this->sounds[WEAPON_EVENT_FIRE]->stop();
		this->sounds[WEAPON_EVENT_FIRE] = 0;
	}
	if (hasSoundSource(WEAPON_EVENT_STOP_FIRE) && isSoundPlaying(WEAPON_EVENT_STOP_FIRE)) {
		this->sounds[WEAPON_EVENT_STOP_FIRE]->stop();
		this->sounds[WEAPON_EVENT_STOP_FIRE] = 0;
	}
}

void AbstractWeapon::setSound(unsigned int event, char *filename, bool singleton)
{
	if (event == WEAPON_EVENT_FIRE || event == WEAPON_EVENT_STOP_FIRE) {
		this->soundSources[event] = SoundManager::getInstance()->getEngine()->addSoundSourceFromFile(filename, ESM_AUTO_DETECT, true);
		this->soundSingelton[event] = singleton;
	}
}