#include "Blobby.h"

Blobby::Blobby()
{
	this->isOnGround = true;
	this->isJumping = false;
	this->isRotating = false;
	this->isWalking = false;
	this->jumpLevel = 0;
	this->direction = 1;
}

Blobby::~Blobby()
{
	this->body = NULL;
}

void Blobby::HandleKeyEvents(unsigned int flag, bool state, int duration)
{
	b2Vec2 velocity = this->body->GetLinearVelocity();

	int time = duration;
	int speed = duration;

	if (time < 100)
	{
		time = 100;
	}

	if (speed > 150)
	{
		speed = 150;
	}
	else if (speed < 50)
	{
		speed = 50;
	}

	switch (flag)
	{
		case LEFT:
			if (state)
			{
				this->MoveLeft(speed);
			}
			else
			{
				this->isWalking = false;
			}
		break;

		case RIGHT:
			if (state)
			{
				this->MoveRight(speed);
			}
			else
			{
				this->isWalking = false;
			}
		break;

		case UP:
			this->isJumping = true;

			if (state)
			{
				if (this->isOnGround)
				{
					this->jumpLevel = 1;
				}

				if (this->jumpLevel == 1)
				{
					this->body->ApplyImpulse(b2Vec2(0, 160), this->body->GetWorldCenter());

					this->isOnGround = false;

					if (time > 300)
					{
						this->jumpLevel = 0;
					}
				}
				else if (!this->isOnGround && this->jumpLevel == 2)
				{
					this->body->SetAngularVelocity((float32)(this->direction * -15));

					this->isRotating = true;

					if (time > 300)
					{
						this->jumpLevel = 3;
					}
				}
			}
			else
			{
				if (this->jumpLevel != 3)
				{
					if (this->jumpLevel == 2)
					{
						this->jumpLevel = 3;
					}
					else
					{
						this->jumpLevel = 2;
					}
				}
			}
		break;

		case DOWN:
			//this->body->SetLinearVelocity(velocity + b2Vec2(0, 0));
		break;
	}
}

void Blobby::MoveLeft(int speed)
{
	this->Move(speed, -1);
}

void Blobby::MoveRight(int speed)
{
	this->Move(speed, 1);
}

void Blobby::Move(int speed, int direction)
{
	this->direction = direction;

	/*if (this->body->GetLinearVelocity().x > 0)
	{
		this->body->SetLinearVelocity(b2Vec2(0, this->body->GetLinearVelocity().y));
	}*/

	/**
	 * TODO: Ground body? Scaling? Incline? Speed control? Mass does not work?
	 */

	int element = direction * abs(speed) * 20;

	this->body->ApplyImpulse(b2Vec2((float32) element, 0), this->body->GetWorldCenter());
			
	this->isWalking = true;
			
	this->ControlSpeeds();
}

#define speed_hori (200 / 15)

void Blobby::ControlSpeeds()
{
	if (this->body->GetLinearVelocity().x > 0 && this->body->GetLinearVelocity().x > speed_hori)
	{
		this->body->SetLinearVelocity(b2Vec2(speed_hori, this->body->GetLinearVelocity().y));
	}
	else if (this->body->GetLinearVelocity().x < 0 && this->body->GetLinearVelocity().x < -speed_hori)
	{
		this->body->SetLinearVelocity(b2Vec2(-speed_hori, this->body->GetLinearVelocity().y));
	}
				
	if(this->body->GetLinearVelocity().y < 0 && this->body->GetLinearVelocity().y < -speed_hori)
	{
		this->body->SetLinearVelocity(b2Vec2(this->body->GetLinearVelocity().y, -speed_hori));
	}
}

void Blobby::SetTextures(Texture *textures)
{
	this->textures = textures;
}

GLuint Blobby::GetTexture()
{
	return this->textures[0].GLid;
}

int Blobby::GetTextureCount()
{
	return 1;
}

char** Blobby::GetTextureFileNames()
{
	static char *fileNames[] = { { "Blobby Warriors\\Data\\blobby\\01.bmp" } };

	return fileNames;
}
