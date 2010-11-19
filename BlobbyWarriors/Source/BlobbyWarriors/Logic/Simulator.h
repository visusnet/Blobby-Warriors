#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <GL/glut.h>

#include <Box2D.h>

class Simulator;

#include "../Debug.h"
#include "Level.h"
#include "Controller\PlayerController.h"
#include "../Model/GameWorld.h"
#include "../Model/PhysicsUtils.h"
#include "../Model/Entity/Factory/BlobbyFactory.h"
#include "../Model/Entity/Factory/GroundFactory.h"
#include "../Model/Entity/Factory/MachineGunFactory.h"
#include "../Model/Entity/Factory/FlamethrowerFactory.h"
#include "../Model/Entity/Factory/BoxFactory.h"
#include "../UI/Graphics/KeyboardHandler.h"
#include "../System/Timeable.h"

class Simulator : public Subscriber, public Timeable
{
public:
	Simulator();
	~Simulator();
	void step();
	void destroyEntities(list<IEntity*> entities);
//	b2Vec2 getActorPosition();
	void update(Publisher *who, UpdateData *what);
	void tick();
private:
	Level *level;
	GameWorld *gameWorld;
	Texture *texture; // shouldn't be here
};

#endif