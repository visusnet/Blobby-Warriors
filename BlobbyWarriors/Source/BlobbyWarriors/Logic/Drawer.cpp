#include "Drawer.h"

Drawer* Drawer::getInstance()
{
	static Guard guard;
	if(Drawer::instance == 0) {
		Drawer::instance = new Drawer();
	}
	return Drawer::instance;
}

void Drawer::draw()
{
	GameWorld *gameWorld = GameWorld::getInstance();
	Blobby *cameraBlobby = gameWorld->getCameraBlobby();

	if (cameraBlobby != 0) {
		b2Vec2 p = Camera::convertWorldToScreen(meter2pixel(cameraBlobby->getBody(0)->GetPosition().x), 300.0f);
		if (p.x < 300) {
			Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 - (300 - int(p.x)), 300));
		} else if (p.x > 500) {
			Camera::getInstance()->setViewCenter(Camera::convertScreenToWorld(400 + (int(p.x) - 500), 300));
		}

		Camera::getInstance()->setViewCenter(b2Vec2(meter2pixel(cameraBlobby->getBody(0)->GetPosition().x), 300.0f));
	}

	// Draw background. Shouldn't be here...
	Texturizer::draw(this->texture, pixel2meter(Camera::getInstance()->getViewCenter().x), pixel2meter(300), 0);

	for (unsigned int i = 0; i < gameWorld->getEntityCount(); i++) {
		IEntity *entity = gameWorld->getEntity(i);
		entity->draw();
	}

	drawString(20, 540, "1 = Flamethrower | 2 = Machine Gun | B = Create Blobby | N = Create Box");
	drawString(20, 555, "W,A,S,D = Move | Mouse = Aim and Fire");
}

void Drawer::drawString(int x, int y, const char *string, ...)
{
	char buffer[128];

	va_list arg;
	va_start(arg, string);
	vsprintf(buffer, string, arg);
	va_end(arg);

	glMatrixMode(GL_PROJECTION);
	glPushMatrix();
	glLoadIdentity();
	int w = glutGet(GLUT_WINDOW_WIDTH);
	int h = glutGet(GLUT_WINDOW_HEIGHT);
	gluOrtho2D(0, w, h, 0);
	glMatrixMode(GL_MODELVIEW);
	glPushMatrix();
	glLoadIdentity();

	glColor3f(1.0f, 1.0f, 1.0f);
//	glColor3f(0.9f, 0.6f, 0.6f);
	glRasterPos2i(x, y);
	int32 length = (int32)strlen(buffer);
	for (int32 i = 0; i < length; ++i)
	{
		glutBitmapCharacter(GLUT_BITMAP_8_BY_13, buffer[i]);
	}

	glPopMatrix();
	glMatrixMode(GL_PROJECTION);
	glPopMatrix();
	glMatrixMode(GL_MODELVIEW);
}

Drawer::Drawer()
{
	this->texture = TextureLoader::createTexture(L"data/images/background/wall.jpg");
	//this->texture = TextureLoader::createTexture(L"data/levels/DiamondMine/vorne1.jpg");
}

Drawer::~Drawer()
{
}

Drawer* Drawer::instance = 0;