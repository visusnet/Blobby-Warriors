#include "Main.h"

int main(int argc, char **argv)
{
	GraphicsEngine *graphicsEngine = GraphicsEngine::getInstance();
	graphicsEngine->initialize(argc, argv);
	graphicsEngine->start();

	return 0;
}