#include "PlayerController.h"

void PlayerController::OnKeyEvent(unsigned int flag, bool state, int duration)
{
	B2_NOT_USED(state);
	B2_NOT_USED(duration);

	if (state)
	{
		switch (flag)
		{
			case LEFT:
				this->blobby->GetBody()->SetLinearVelocity(b2Vec2(-10, this->blobby->GetBody()->GetLinearVelocity().y));
				break;
			case RIGHT:
				this->blobby->GetBody()->SetLinearVelocity(b2Vec2(10, this->blobby->GetBody()->GetLinearVelocity().y));
				break;
			case UP:
				this->blobby->GetBody()->ApplyForce(b2Vec2(0, 100), this->blobby->GetBody()->GetWorldCenter());
				break;
		}
	}
}