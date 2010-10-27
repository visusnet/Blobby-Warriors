#ifndef MAIN_H
#define MAIN_H

#ifdef _DEBUG
#pragma comment(linker, "/SUBSYSTEM:CONSOLE")
#else
#pragma comment(linker, "/SUBSYSTEM:WINDOWS /ENTRY:\"mainCRTStartup\"")
#endif

#include <iostream>

#include "Graphics\GraphicsEngine.h"

using namespace std;

class Main : public Subscriber
{
public:
	Main(int argc, char **argv);
	void update(Publisher *who, UpdateData *what = 0);
private:
	Simulator *simulator;
};

#endif