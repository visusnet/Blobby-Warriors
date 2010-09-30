
#include "GameObject.h"

GameObject::GameObject(void)
{
}

GameObject::~GameObject(void)
{
}

void GameObject::SetBody(b2Body *body)
{
	this->body = body;
}

b2Body* GameObject::GetBody()
{
	return this->body;
}

float GameObject::GetPositionX()
{
	return this->body->GetPosition().x;
}

float GameObject::GetPositionY()
{
	return this->body->GetPosition().y;
}