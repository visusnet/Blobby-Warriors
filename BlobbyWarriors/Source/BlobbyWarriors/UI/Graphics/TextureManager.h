#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <wchar.h>

#include <list>

#include "Texture.h"
#include "TextureLoader.h"
#include "Texturizer.h"

using namespace std;

struct TextureInfo
{
	wchar_t *filename;
	Color *color;
	Color *colorKey;
	Texture *texture;
};

class TextureManager
{
public:
	static TextureManager* getInstance();
	Texture* loadTexture(wchar_t *filename, Color *color = 0, Color *colorKey = 0);
private:
	TextureManager();
	TextureManager(const TextureManager&);
	~TextureManager();

	static TextureManager *instance;

	list<TextureInfo*> textures;

	class Guard
	{
	public:
		~Guard()
		{
			if (TextureManager::instance != 0) {
				delete TextureManager::instance;
			}
		}
	};
	friend class Guard;
};

inline bool wcharIsEqual(wchar_t *a, wchar_t *b) {
	if (a == 0 && b == 0) {
		return true;
	} else if (a == 0 || b == 0) {
		return false;
	}
	return wmemcmp(a, b, wcslen(a)) == 0;
}

inline bool colorIsEqual(Color *a, Color *b) {
	if (a == 0 && b == 0) {
		return true;
	} else if (a == 0 || b == 0) {
		return false;
	}
	return a->r == b->r && a->g == b->g && a->b == b->b && a->a == b->a;
}

#endif