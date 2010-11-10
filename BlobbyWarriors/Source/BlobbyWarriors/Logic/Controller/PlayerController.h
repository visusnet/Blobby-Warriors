#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "AbstractController.h"
#include "../../Model/Entity/Blobby.h"
#include "../../Model/Entity/Ground.h"
#include "../../UI/Graphics/GraphicsEngine.h"
#include "../../UI/Graphics/KeyboardHandler.h"
#include "../../UI/Graphics/MouseHandler.h"

class PlayerController : public AbstractController, public Subscriber
{
public:
	PlayerController();
	void update(Publisher *who, UpdateData *what = 0);
	bool handleKeyEvent(KeyEventArgs *keyEventArgs);
	bool handleMouseEvent(MouseEventArgs *mouseEventArgs);
};

#endif