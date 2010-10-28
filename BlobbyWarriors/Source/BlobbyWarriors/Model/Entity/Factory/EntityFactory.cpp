#include "EntityFactory.h"

IEntity* EntityFactory::create()
{
	return this->create(this->getDefaultProperties());
}