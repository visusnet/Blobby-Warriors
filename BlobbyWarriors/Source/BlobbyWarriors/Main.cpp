#include "Main.h"

int main(int argc, char **argv)
{
	new Main(argc, argv);

	return 0;
}

Main::Main(int argc, char **argv)
{
	this->accum = 0;
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);

	this->graphicsEngine = GraphicsEngine::getInstance();
	this->graphicsEngine->initialize(argc, argv);

	this->simulator = new Simulator();

	this->graphicsEngine->subscribe(this);

	SoundManager::getInstance()->getEngine()->play2D("data/sound/vaporrush.ogg", true);

	this->graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
/*	int start = glutGet(GLUT_ELAPSED_TIME);

	this->accum += this->previousTicks;
	while (accum > PHYSICS_TIMESTEP) {
		this->accum -= PHYSICS_TIMESTEP;*/
//	}

	this->simulator->step(float(glutGet(GLUT_ELAPSED_TIME) - this->previousTicks));
//	Drawer::getInstance()->draw();

	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);

//	debug("prevTicks: %d", this->previousTicks);
}