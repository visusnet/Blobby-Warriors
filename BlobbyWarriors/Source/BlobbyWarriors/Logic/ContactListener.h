#ifndef CONTACTLISTENER_H
#define CONTACTLISTENER_H

#include <Box2D.h>

#include "../PublishSubscribe.h"

enum ContactType
{
	CONTACT_TYPE_UNKNOWN = 0,
	CONTACT_TYPE_BEGIN = 1,
	CONTACT_TYPE_END = 2,
	CONTACT_TYPE_PRESOLVE = 3,
	CONTACT_TYPE_POSTSOLVE = 4
};

class ContactEventArgs : public UpdateData
{
public:
	int type;
	b2Contact *contact;
	b2Manifold *oldManifold;
	b2ContactImpulse *impulse;
};

class ContactListener : public b2ContactListener, public Publisher
{
public:
	static ContactListener* getInstance();

	void BeginContact(b2Contact *contact);
	void EndContact(b2Contact *contact);
	void PreSolve(b2Contact *contact, const b2Manifold *oldManifold);
	void PostSolve(b2Contact *contact, const b2ContactImpulse *impulse);
private:
	ContactListener();
	ContactListener(const ContactListener&);
	~ContactListener();

	static ContactListener *instance;

	class Guard
	{
	public:
		~Guard()
		{
			if (ContactListener::instance != 0) {
				delete ContactListener::instance;
			}
		}
	};
	friend class Guard;
};

#endif