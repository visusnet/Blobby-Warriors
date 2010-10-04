#include "BoundaryListener.h"

void BoundaryListener::Violation(b2Body* body)
{
	if (game->m_bomb != body)
	{
		//game->BoundaryViolated(body);
	}
}
