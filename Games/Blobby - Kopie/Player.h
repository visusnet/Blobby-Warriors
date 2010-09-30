#pragma once

#include "World.h"
#include "Blobby.h"
#include "PlayerController.h"

class Player
{
public:
	static Player* GetInstance();
	Blobby *GetBlobby();
	void Renew();
private:
	Player(void);
	~Player(void);
	static Player *instance;
	Blobby *blobby;
};
