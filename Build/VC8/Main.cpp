#include <stdio.h>

#include "glui/GL/glui.h"

#include "Render.h"
#include "Test.h"
#include "Game.h"

void Resize(int32 w, int32 h)
{
	width = w;
	height = h;

	GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
	glViewport(tx, ty, tw, th);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float32 ratio = float32(tw) / float32(th);

	b2Vec2 extents(ratio * 25.0f, 25.0f);
	extents *= viewZoom;

	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	// L/R/B/T
	gluOrtho2D(lower.x, upper.x, lower.y, upper.y);
}

b2Vec2 ConvertScreenToWorld(int32 x, int32 y)
{
	float32 u = x / float32(tw);
	float32 v = (th - y) / float32(th);

	float32 ratio = float32(tw) / float32(th);
	b2Vec2 extents(ratio * 25.0f, 25.0f);
	extents *= viewZoom;

	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	b2Vec2 p;
	p.x = (1.0f - u) * lower.x + u * upper.x;
	p.y = (1.0f - v) * lower.y + v * upper.y;

	return p;
}

// This is used to control the frame rate (60Hz).
void Timer(int)
{
	glutSetWindow(mainWindow);
	glutPostRedisplay();
	glutTimerFunc(framePeriod, Timer, 0);
}

void KeyEventDown(unsigned int key)
{
	keyList->GetKeyByFlag(key)->Down();
}

void KeyEventUp(unsigned int key)
{
	keyList->GetKeyByFlag(key)->Up();
}

void Update(KeyList *keyList)
{
	for (int i = 0; i < keyList->Size(); i++)
	{
		Key *key = keyList->GetKeyById(i);

		if (key->IsPressed() || key->HasChanged())
		{
			game->playerBlobby->HandleKeyEvents(key->GetFlag(), key->isPressed, key->duration);
		}
	}
}

void SimulationLoop()
{
	if (game == NULL)
	{
		return;
	}

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();

	settings.hz = settingsHz;
	
	keyEventHandler->Step();
	Update(keyList);

#ifdef DEBUG
	DrawString(10, 100, keyList->GetKeyById(0)->isPressed ? "pressed since %d" : "not pressed", keyList->GetKeyById(0)->duration);
	DrawString(10, 120, keyList->GetKeyById(1)->isPressed ? "pressed since %d" : "not pressed", keyList->GetKeyById(1)->duration);
	DrawString(10, 140, keyList->GetKeyById(2)->isPressed ? "pressed since %d" : "not pressed", keyList->GetKeyById(2)->duration);
	DrawString(10, 160, keyList->GetKeyById(3)->isPressed ? "pressed since %d" : "not pressed", keyList->GetKeyById(3)->duration);
	DrawString(10, 180, "Jump Level: %d", game->playerBlobby->jumpLevel);
	DrawString(10, 200, "Is jumping: %s", game->playerBlobby->isJumping ? "true" : "false");
	DrawString(10, 220, "Is on ground: %s", game->playerBlobby->isOnGround ? "true" : "false");
#endif

	game->Step(&settings);

	b2Body *body = game->playerBlobby->body;
	texturizer->Draw(0, body->GetPosition().x, body->GetPosition().y, 40, 48, body->GetAngle());

	glutSwapBuffers();
/*
	if (testSelection != testIndex)
	{
		testIndex = testSelection;
		delete test;
		entry = g_testEntries + testIndex;
		test = entry->createFcn();
		viewZoom = 1.0f;
		viewCenter.Set(0.0f, 20.0f);
		Resize(width, height);
	}*/
}

void Mouse(int32 button, int32 state, int32 x, int32 y)
{
	printf("Mouse: %i %i %i %i\n", button, state, x, y);
/*	// Use the mouse to move things around.
	if (button == GLUT_LEFT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{
			b2Vec2 p = ConvertScreenToWorld(x, y);
			test->MouseDown(p);
		}
		
		if (state == GLUT_UP)
		{
			test->MouseUp();
		}
	} else if (button == GLUT_RIGHT_BUTTON)
	{
		if (state == GLUT_DOWN)
		{	
			lastp = ConvertScreenToWorld(x, y);
			rMouseDown = true;
		}

		if (state == GLUT_UP)
		{
			rMouseDown = false;
		}
	}*/
}

void MouseMotion(int32 x, int32 y)
{
	printf("MouseMotion: %i %i\n", x, y);
/*	b2Vec2 p = ConvertScreenToWorld(x, y);
	test->MouseMove(p);
	
	if (rMouseDown){
		b2Vec2 diff = p - lastp;
		viewCenter.x -= diff.x;
		viewCenter.y -= diff.y;
		Resize(width, height);
		lastp = ConvertScreenToWorld(x, y);
	}*/
}

void MouseWheel(int wheel, int direction, int x, int y)
{
	printf("MouseWheel: %i %i %i %i\n", wheel, direction, x, y);
	/*B2_NOT_USED(wheel);
	B2_NOT_USED(x);
	B2_NOT_USED(y);
	if (direction > 0) {
		viewZoom /= 1.1f;
	} else {
		viewZoom *= 1.1f;
	}
	Resize(width, height);*/
}

void Pause(int)
{
	settings.pause = !settings.pause;
}

void SingleStep(int)
{
	settings.pause = 1;
	settings.singleStep = 1;
}

void InitializeGlut(int argc, char** argv)
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
	glutInitWindowSize(width, height);
	glShadeModel(GL_SMOOTH);
	glutSetKeyRepeat(GLUT_KEY_REPEAT_ON);

	char title[32];
	sprintf(title, "Box2D Version %d.%d.%d", b2_version.major, b2_version.minor, b2_version.revision);
	mainWindow = glutCreateWindow(title);

	//glutSetOption (GLUT_ACTION_ON_WINDOW_CLOSE, GLUT_ACTION_GLUTMAINLOOP_RETURNS);

	glutDisplayFunc(SimulationLoop);
	GLUI_Master.set_glutReshapeFunc(Resize);  
	GLUI_Master.set_glutMouseFunc(Mouse);

	keyList = new KeyList();
	keyList->Add(LEFT);
	keyList->Add(RIGHT);
	keyList->Add(UP);
	keyList->Add(DOWN);

	keyEventHandler = new KeyEventHandler(keyList);
	keyEventHandler->SetKeyDownFunction(KeyEventDown);
	keyEventHandler->SetKeyUpFunction(KeyEventUp);

#ifdef FREEGLUT
	glutMouseWheelFunc(MouseWheel);
#endif
	glutMotionFunc(MouseMotion);

	glutTimerFunc(framePeriod, Timer, 0);

	glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

	texturizer = new Texturizer();

	updatePrevious = glutGet(GLUT_ELAPSED_TIME);
}

int main(int argc, char** argv)
{
	InitializeGlut(argc, argv);

	settings.drawShapes = 1;
	settings.drawStats = 1;

	game = new Game();

	texturizer->LoadImages(game->playerBlobby);

	glutMainLoop();

	return 0;
}
