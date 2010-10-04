#ifndef BLOBBY_H
#define BLOBBY_H

#include "glui/GL/glui.h"
#include "Box2D.h"

#include "RigidBody.h"

#include "KeyEventHandler.h"

class Blobby : public RigidBody
{
public:
	Blobby();
	~Blobby();
	void HandleKeyEvents(unsigned int flag, bool state, int duration);
	void MoveLeft(int speed);
	void MoveRight(int speed);
	bool isOnGround;
	bool isJumping;
	bool isRotating;
	bool isWalking;
	int jumpLevel;
	int direction;
	b2Body *body;

	void SetTextures(Texture *textures);
	GLuint GetTexture();
	int GetTextureCount();
	char** GetTextureFileNames();

protected:
	friend class Game;

private:
	void Move(int speed, int direction);
	void ControlSpeeds();
	Texture *textures;
};

#endif
