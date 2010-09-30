#include "GameObjectCreator.h"

GameObject* GameObjectCreator::CreateObject(GameObjectSettings settings)
{
	return this->Create(settings);
}

GameObject* GameObjectCreator::CreateObject()
{
	return this->Create(this->GetDefaultSettings());
}