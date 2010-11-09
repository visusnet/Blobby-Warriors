#include "Main.h"

int main(int argc, char **argv)
{
	new Main(argc, argv);

	return 0;
}

Main::Main(int argc, char **argv)
{
	this->graphicsEngine = GraphicsEngine::getInstance();
	this->graphicsEngine->subscribe(this);
	this->graphicsEngine->initialize(argc, argv);

	this->simulator = new Simulator();

	this->graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
	this->simulator->step();
}