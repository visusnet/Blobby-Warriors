#include "PublishSubscribe.h"

void Publisher::subscribe(Subscriber *s)
{
	this->subscribers.push_back(s);
}

void Publisher::unsubscribe(Subscriber *s)
{
	this->removableSubscribers.push_back(s);
}

void Publisher::notify(UpdateData *what)
{
	// Kill old subscribers first.
	for(list<Subscriber*>::iterator it = this->removableSubscribers.begin(); it != this->removableSubscribers.end(); ++it) {
		this->subscribers.remove(*it);
	}
	this->removableSubscribers.clear();
	// Notify the rest!
	for(list<Subscriber*>::iterator it = this->subscribers.begin(); it != this->subscribers.end(); ++it) {
		if (*it != 0) {
			(*it)->update(this, what);
		}
	}
}