#ifndef PUBLISHSUBSCRIBE_H
#define PUBLISHSUBSCRIBE_H

#include <vector>
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
	Publisher() { this->level = 0; }
	void subscribe(Subscriber *s);
	void unsubscribe(Subscriber *s);
	void notify(UpdateData *what = 0);
private:
	list<Subscriber*> subscribers;
	vector<Subscriber*> removableSubscribers;
	int level;
};

#endif