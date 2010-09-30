#include "Player.h"

Player* Player::instance = 0;

Player* Player::GetInstance()
{
	if (instance == 0)
	{
		instance = new Player();
	}

	return instance;
}


Player::Player(void)
{
	GameObjectCreator *creator = new BlobbyCreator();
	this->blobby = (Blobby*)creator->CreateObject();
	this->blobby->SetController(new PlayerController());
}

Player::~Player(void)
{
}

Blobby* Player::GetBlobby()
{
	return this->blobby;
}

void Player::Renew()
{
	instance = 0;
}
