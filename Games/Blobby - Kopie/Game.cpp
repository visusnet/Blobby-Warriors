#include "Game.h"

Game::Game(void)
{
	World *world = World::GetInstance();
	world->Initialize();

	keyList = new KeyList();
	keyList->Add(LEFT);
	keyList->Add(RIGHT);
	keyList->Add(UP);
	keyList->Add(DOWN);

	keyEventHandler = new KeyEventHandler(keyList);
	keyEventHandler->SetKeyDownFunction(KeyEventDown);
	keyEventHandler->SetKeyUpFunction(KeyEventUp);
}

Game::~Game(void)
{
}

void ResizeCallback(int w, int h)
{
	width = w;
	height = h;

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluOrtho2D(viewCenter.x - width / 2, viewCenter.x + width / 2, viewCenter.y - height / 2, viewCenter.y + height / 2);
	//gluOrtho2D(0, 800, 0, 600);
	/*GLUI_Master.get_viewport_area(&tx, &ty, &tw, &th);
	glViewport(tx, ty, tw, th);

	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	float32 ratio = float32(tw) / float32(th);

	b2Vec2 extents(ratio * 25.0f, 25.0f);
	extents *= viewZoom;

	b2Vec2 lower = viewCenter - extents;
	b2Vec2 upper = viewCenter + extents;

	// L/R/B/T
	gluOrtho2D(lower.x, upper.x, lower.y, upper.y);*/
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
			Controller *controller = Player::GetInstance()->GetBlobby()->GetController();

			if (controller != 0)
			{
				controller->OnKeyEvent(key->GetFlag(), key->isPressed, key->duration);
			}
		}
	}
}


void MouseCallback(int button, int state, int x, int y)
{
	B2_NOT_USED(button);
	B2_NOT_USED(state);
	B2_NOT_USED(x);
	B2_NOT_USED(y);
}

void DrawCallback()
{
	GraphicsEngine::ClearScreen();

	keyEventHandler->Step();
	Update(keyList);

	World::GetInstance()->Step();

	/**
	 * Reposition camera
	 */
	b2Vec2 position = Player::GetInstance()->GetBlobby()->GetBody()->GetPosition();
	b2Vec2 cameraPositon;
	cameraPositon.x = (viewCenter.x - position.x * SCALING_FACTOR > 10) ? position.x * SCALING_FACTOR + 10 : (viewCenter.x - position.x * SCALING_FACTOR < -10) ? position.x * SCALING_FACTOR - 10 : viewCenter.x;
	cameraPositon.y = (viewCenter.y - position.y * SCALING_FACTOR > 10) ? position.y * SCALING_FACTOR + 10 : (viewCenter.y - position.y * SCALING_FACTOR < -10) ? position.y * SCALING_FACTOR - 10 : viewCenter.y;
	viewCenter.Set(cameraPositon.x, cameraPositon.y);
	ResizeCallback(width, height);

	GraphicsEngine::Flush();
}

void IdleCallback()
{
}

int main(int argc, char **argv)
{
	new Game;

	GraphicsEngine *graphicsEngine = new GraphicsEngine(argc, argv);
	graphicsEngine->SetResizeCallback(ResizeCallback);
	graphicsEngine->SetMouseCallback(MouseCallback);
	graphicsEngine->SetDrawCallback(DrawCallback);
	graphicsEngine->SetIdleCallback(IdleCallback);
	graphicsEngine->MainLoop();

	return 0;
}