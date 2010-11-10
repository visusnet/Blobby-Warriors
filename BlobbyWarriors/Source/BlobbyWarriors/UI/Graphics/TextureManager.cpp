#include "TextureManager.h"

TextureManager* TextureManager::getInstance()
{
	static Guard guard;
	if(TextureManager::instance == 0) {
		TextureManager::instance = new TextureManager();
	}
	return TextureManager::instance;
}

Texture* TextureManager::loadTexture(wchar_t *filename, Color *color, Color *colorKey)
{
	for (list<TextureInfo*>::iterator it = this->textures.begin(); it != this->textures.end(); ++it) {
		TextureInfo *textureInfo = *it;
		if (wcharIsEqual(textureInfo->filename, filename) && colorIsEqual(textureInfo->color, color) && colorIsEqual(textureInfo->colorKey, colorKey)) {
			return textureInfo->texture;
		}
	}

	TextureInfo *textureInfo = new TextureInfo();
	textureInfo->filename = filename;
	textureInfo->color = color;
	textureInfo->colorKey = colorKey;
	textureInfo->texture = TextureLoader::createTexture(filename, color, colorKey);
	this->textures.push_back(textureInfo);
	return textureInfo->texture;
}

TextureManager::TextureManager()
{

}

TextureManager::~TextureManager()
{
	for (list<TextureInfo*>::iterator it = this->textures.begin(); it != this->textures.end(); ++it) {
		TextureInfo *textureInfo = *it;
		delete textureInfo->texture;
		delete textureInfo;
	}
}

TextureManager* TextureManager::instance = 0;