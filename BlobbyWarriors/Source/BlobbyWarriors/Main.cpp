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
	this->simulator->setInterval(16);
	this->simulator->start();

	SoundManager::getInstance()->getEngine()->play2D("data/sound/vaporrush.ogg", true);

	this->graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
	// old:
	//	this->simulator->step();
	Drawer::getInstance()->draw();
}