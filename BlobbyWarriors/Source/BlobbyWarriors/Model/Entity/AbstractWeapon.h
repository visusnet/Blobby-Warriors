#ifndef ABSTRACTWEAPON_H
#define ABSTRACTWEAPON_H

#define WEAPON_OFFSET_DUCKED_BLOBBY -0.2f

class AbstractWeapon;

#include "AbstractEntity.h"
#include "IWearable.h"
#include "../../UI/Sound/SoundManager.h"

enum WeaponEvent
{
	WEAPON_EVENT_FIRE = 0,
	WEAPON_EVENT_STOP_FIRE = 1
};

#define hasSoundSource(event) (this->soundSources[event] != 0)
#define isSoundPlaying(sound) (this->sounds[sound] != 0)

class AbstractWeapon : public AbstractEntity, public IWearable
{
public:
	AbstractWeapon();
	void fire(b2Vec2 direction, bool constantFire, bool isPlayer = false);
	void stopFire();
	virtual void onFire(b2Vec2 direction, bool constantFire, bool isPlayer = false) = 0;
	virtual void onStopFire();
	virtual void draw();
	void setActive(bool isActive);
protected:
	void setSound(unsigned int event, char *filename, bool singleton = true);

	bool isActive;
private:
	ISoundSource *soundSources[2];
	ISound *sounds[2];
	bool soundSingelton[2];
};

#endif