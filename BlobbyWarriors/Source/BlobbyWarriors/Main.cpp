#include "Main.h"

int main(int argc, char **argv)
{
	new Main(argc, argv);

	return 0;
}

Main::Main(int argc, char **argv)
{
	this->simulator = new Simulator();

	GraphicsEngine *graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->subscribe(this);
	graphicsEngine->initialize(argc, argv);
	graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
	this->simulator->step();
}