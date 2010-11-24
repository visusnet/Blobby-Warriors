#include "Main.h"

int main(int argc, char **argv)
{
	new Main(argc, argv);

	return 0;
}

Main::Main(int argc, char **argv)
{
	this->accumilator = 0;
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);

	this->graphicsEngine = GraphicsEngine::getInstance();
	this->graphicsEngine->initialize(argc, argv);

	this->simulator = new Simulator(new Level());

	this->graphicsEngine->subscribe(this);

	SoundManager::getInstance()->getEngine()->play2D("data/sound/vaporrush.ogg", true);

	this->graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
	int deltaTime = min(max(glutGet(GLUT_ELAPSED_TIME) - this->previousTicks, 0), 1000);
	this->accumilator += deltaTime / 1000.0f;
	float timeStep = 1.0f / 62.5f;
	while (accumilator > timeStep) {
		this->simulator->step(timeStep);
		this->accumilator -= timeStep;
	}

	Drawer::getInstance()->draw();

	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);
}
