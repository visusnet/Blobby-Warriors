#include "KeyList.h"

void KeyList::Add(unsigned int flag)
{
	this->keys.push_back(new Key(flag));
}

void KeyList::Remove(Key *key)
{
	for (int i = 0; i < this->Size(); i++)
	{
		if (this->keys.at(i)->GetFlag() == key->GetFlag())
		{
			this->keys.erase(this->keys.begin() + i);

			break;
		}
	}
}

int KeyList::Size()
{
	return (int) this->keys.size();
}

Key* KeyList::GetKeyByFlag(unsigned int flag)
{
	for (int i = 0; i < this->Size(); i++)
	{
		if (this->keys.at(i)->GetFlag() == flag)
		{
			return this->keys.at(i);
		}
	}

	return NULL;
}

Key* KeyList::GetKeyById(int id)
{
	if (0 <= id && id < this->Size())
	{
		return this->keys.at(id);
	}

	return NULL;
}
