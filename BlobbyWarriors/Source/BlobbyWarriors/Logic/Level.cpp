#include "Level.h"
#include <math.h>

Level::Level()
{
}

void Level::initialize()
{
	this->parseXMLFile("data/levels/DiamondMine/level.xml");
}

void Level::parseXMLFile(const char *uri)
{
	// Initialize COM library.
	OleInitialize(0);

	XML* xmlDoc = 0;
	
	// Load from file or URL.
	FILE* fp = fopen(uri, "rb");
	if (fp) {
		// Load from file.
		fclose(fp);
		xmlDoc = new XML(uri);
	} else {
		// Load from URL.
		xmlDoc = new XML(uri, XML_LOAD_MODE_LOCAL_FILE);
	}

	// Check parse status and do integrity test. 0 OK , 1 Header warning (not fatal) , 2 Error in parse (fatal)
	if (xmlDoc->ParseStatus() == 2 || !xmlDoc->IntegrityTest()) {
		debug("Error: XML file %s is corrupt (or not a XML file).", uri);
		delete xmlDoc;
		return;
	}

	// Compress level XML in memory.
	xmlDoc->CompressMemory();

	XMLElement *rootNode = xmlDoc->GetRootElement();

	this->parseElement(rootNode);

	delete xmlDoc;
}

void Level::parseElement(XMLElement *element)
{
	EntityFactory *entityFactory = 0;
	EntityProperties *properties = 0;

	// Get element name.
	char* elementName = new char[element->GetElementName(0) + 1];
	element->GetElementName(elementName);

	XMLVariable** variables = element->GetVariables();

	if(strncmp(elementName, "Ground", sizeof(elementName)) == 0) {
		// TODO: The position of the XML attribute shouldn't be relevant.
		b2Vec2 position1 = b2Vec2(variables[0][0].GetValueFloat(), variables[1][0].GetValueFloat());
		b2Vec2 position2 = b2Vec2(variables[2][0].GetValueFloat(), variables[3][0].GetValueFloat());
		float friction = variables[4][0].GetValueFloat();

		// Calculate body center and dimensions.
		b2Vec2 offset = position2 - position1;
		float length = sqrt((offset.x * offset.x) + (offset.y * offset.y) * 0.5);
		float angle = atan2(offset.y, offset.x);
		b2Vec2 position = position1 - b2Vec2(cos(angle) * length, sin(angle) * length);
		b2Vec2 shift = b2Vec2(abs(position2.x - position1.x), abs(position2.y - position1.y));
		if (position1.x >= position2.x || position1.y >= position2.y) {
			shift.y *= -1;
		}
		position += shift;

		entityFactory = new GroundFactory();
		properties = &entityFactory->getDefaultProperties();

		properties->x = position.x;
		properties->y = position.y;
		properties->width = length;
		properties->height = 10;
		properties->angle = angle;
	} else {
		int numChildren = element->GetChildrenNum();
		// Iterate over all elements.
		for(int i = 0; i < numChildren; i++) {
			XMLElement* childElement = element->GetChildren()[i];

			this->parseElement(childElement);
		}
	}

	delete[] elementName;

	if (entityFactory != 0 && properties != 0) {
		entityFactory->create(*properties);
	}
}