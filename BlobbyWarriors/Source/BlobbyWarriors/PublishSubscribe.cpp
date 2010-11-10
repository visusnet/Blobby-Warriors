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
	if (this->level == 0) {
		for(vector<Subscriber*>::iterator it = this->removableSubscribers.begin(); it != this->removableSubscribers.end(); it++) {
			this->subscribers.remove(*it);
		}
		this->removableSubscribers.clear();
	}
	// Notify the rest!
	this->level++;
	for(list<Subscriber*>::iterator it = this->subscribers.begin(); it != this->subscribers.end(); it++) {
		Subscriber *subscriber = *it;
		if (subscriber != 0) {
			subscriber->update(this, what);
		}
	}
	this->level--;
}