#include "DestructionListener.h"

void DestructionListener::SayGoodbye(b2Joint* joint)
{
	if (game->m_mouseJoint == joint)
	{
		game->m_mouseJoint = NULL;
	}
	else
	{
		//game->JointDestroyed(joint);
	}
}
