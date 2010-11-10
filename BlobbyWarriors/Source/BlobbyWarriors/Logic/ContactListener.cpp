#include "ContactListener.h"

ContactListener* ContactListener::getInstance()
{
	static Guard guard;
	if(ContactListener::instance == 0) {
		ContactListener::instance = new ContactListener();
	}
	return ContactListener::instance;
}

void ContactListener::BeginContact(b2Contact *contact)
{
	ContactEventArgs *eventArgs = new ContactEventArgs();
	eventArgs->type = CONTACT_TYPE_BEGIN;
	eventArgs->contact = contact;
	this->notify(eventArgs);
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

void ContactListener::EndContact(b2Contact *contact)
{
	ContactEventArgs *eventArgs = new ContactEventArgs();
	eventArgs->type = CONTACT_TYPE_END;
	eventArgs->contact = contact;
	this->notify(eventArgs);
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

void ContactListener::PreSolve(b2Contact *contact, const b2Manifold *oldManifold)
{
	ContactEventArgs *eventArgs = new ContactEventArgs();
	eventArgs->type = CONTACT_TYPE_PRESOLVE;
	eventArgs->contact = contact;
	eventArgs->oldManifold = new b2Manifold(*oldManifold);
	this->notify(eventArgs);
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

void ContactListener::PostSolve(b2Contact *contact, const b2ContactImpulse *impulse)
{
	ContactEventArgs *eventArgs = new ContactEventArgs();
	eventArgs->type = CONTACT_TYPE_POSTSOLVE;
	eventArgs->contact = contact;
	eventArgs->impulse = new b2ContactImpulse(*impulse);
	this->notify(eventArgs);
	if (eventArgs != 0) {
		delete eventArgs;
	}
}

ContactListener::ContactListener()
{
}

ContactListener::~ContactListener()
{
}

ContactListener *ContactListener::instance = 0;