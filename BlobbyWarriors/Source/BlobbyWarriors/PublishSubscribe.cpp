#include "PublishSubscribe.h"

void Publisher::subscribe(Subscriber *s)
{
	this->subscribers.push_back(s);
}

void Publisher::unsubscribe(Subscriber *s)
{
	this->subscribers.remove(s);
}

void Publisher::notify(UpdateData *what)
{
	list<Subscriber*>::iterator p;
	for(p = this->subscribers.begin(); p != this->subscribers.end(); p++) {
		(*p)->update(this, what);
	}
}