#ifndef LEVEL_H
#define LEVEL_H

#include "../System/xml.h"
#include "../Debug.h"

#include "../Model/Entity/Factory/GroundFactory.h"

class Level
{
public:
	Level();
	void initialize();
private:
	void parseXMLFile(const char *uri);
	void parseElement(char *elementName, XMLVariable **variables);
};

#endif