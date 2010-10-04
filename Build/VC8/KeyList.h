#ifndef KEY_LIST_H
#define KEY_LIST_H

#include "Key.h"

#include <vector>

using namespace std;

class KeyList
{
public:
	void Add(unsigned int flag);
	void Remove(Key *key);
	int Size();
	Key* GetKeyByFlag(unsigned int flag);
	Key* GetKeyById(int id);

private:
	vector<Key*> keys;
};

#endif
