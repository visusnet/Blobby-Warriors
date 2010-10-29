#ifndef PUBLISHSUBSCRIBE_H
#define PUBLISHSUBSCRIBE_H

#include <list>

using namespace std;

class UpdateData {
public:
	virtual ~UpdateData() {}
};

class Publisher;

class Subscriber
{
public:
	virtual void update(Publisher *who, UpdateData *what = 0) = 0;
};

class Publisher
{
public:
	void subscribe(Subscriber *s);
	void unsubscribe(Subscriber *s);
	void notify(UpdateData *what = 0);
private:
	list<Subscriber*> subscribers;
	list<Subscriber*> removableSubscribers;
};

#endif