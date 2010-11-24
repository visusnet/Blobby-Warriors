#include "Main.h"

int main(int argc, char **argv)
{
	new Main(argc, argv);

	return 0;
}

Main::Main(int argc, char **argv)
{
	this->accumulator = 0;
	this->previousTicks = glutGet(GLUT_ELAPSED_TIME);
	this->simulator = 0;
	this->isLoading = false;

	KeyboardHandler::getInstance()->subscribe(this);

	this->graphicsEngine = GraphicsEngine::getInstance();
	this->graphicsEngine->initialize(argc, argv);
	this->graphicsEngine->subscribe(this);
	this->graphicsEngine->start();
}

void Main::update(Publisher *who, UpdateData *what)
{
	KeyEventArgs *keyEventArgs = dynamic_cast<KeyEventArgs*>(what);
	if (keyEventArgs != 0) {
		this->handleKeyEvent(keyEventArgs);
	}

	if (this->simulator != 0) {
        int currentTicks = glutGet(GLUT_ELAPSED_TIME);
        int deltaTime = min(max(currentTicks - this->previousTicks, 0), 1000);
		this->accumulator += deltaTime / 1000.0f;
		float timeStep = 1.0f / 60.5f;
		while (this->accumulator > timeStep) {
			this->simulator->step(timeStep);
			this->accumulator -= timeStep;
		}
		Drawer::getInstance()->drawSimulation();

		this->previousTicks = currentTicks;
	} else if (this->isLoading) {
		Drawer::getInstance()->drawLoadScreen();
	} else {
		Drawer::getInstance()->drawMenu();
	}
}

void Main::handleKeyEvent(KeyEventArgs *eventArgs)
{
	if (this->simulator == 0) {
		this->isLoading = true;
		// TODO: Put this into another thread, so we can wait
		// until the simulator is initialized.
		this->simulator = new Simulator(new Level());
		this->isLoading = false;
	}
}