#include "TextureLoader.h"

TextureLoader::TextureLoader()
{
	if (ilGetInteger(IL_VERSION_NUM) < IL_VERSION)
	{
		printf("ERROR: Could not load DevIL\n");
	}

	ilInit();

	ilutRenderer(ILUT_OPENGL);
}

bool TextureLoader::LoadImage(char *filename, Texture *texture)
{
	ilGenImages(1, &texture->ILid);

	ilBindImage(texture->ILid);

	if (ilLoadImage(filename))
	{
		if (!ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE))
		{
			return false;
		}

		texture->width = ilGetInteger(IL_IMAGE_WIDTH);
		texture->height = ilGetInteger(IL_IMAGE_HEIGHT);
		texture->pwidth = NextPowerOfTwo(ilGetInteger(IL_IMAGE_WIDTH));
		texture->pheight = NextPowerOfTwo(ilGetInteger(IL_IMAGE_HEIGHT));
		
		if (!iluScale(texture->pwidth,
					 texture->pheight,
					 ilGetInteger(IL_IMAGE_DEPTH)))
		{
			return false;
		}

		glGenTextures(1, &texture->GLid);
		glBindTexture(GL_TEXTURE_2D, texture->GLid);

		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

		glPixelStoref(GL_UNPACK_ALIGNMENT, 1);

		ILubyte *imageData = ilGetData();
		
		this->SetColorKey(imageData, texture->pwidth * texture->pheight, new Color(0, 0, 0));

		this->Colorize(imageData, texture->pwidth * texture->pheight, new Color(255, 0, 0));
		
		glTexImage2D(GL_TEXTURE_2D, 0,
					 ilGetInteger(IL_IMAGE_BPP),
					 ilGetInteger(IL_IMAGE_WIDTH),
					 ilGetInteger(IL_IMAGE_HEIGHT), 0,
					 ilGetInteger(IL_IMAGE_FORMAT),
					 GL_UNSIGNED_BYTE,
					 imageData);
	}
	else
	{
		return false;
	}

	ilDeleteImages(1, &texture->ILid);

	return true;
}

int TextureLoader::Round(double x)
{
	return (int)(x > 0 ? x + 0.5f : x - 0.5f);
}

int TextureLoader::NextPowerOfTwo(int x)
{
	double logbase2 = log((double)x) / log(2.0f);
	return TextureLoader::Round(pow(2, ceil(logbase2)));
}

void TextureLoader::SetColorKey(ILubyte *imageData, int size, Color *color)
{
	for (int i = 0; i < size * 4; i += 4)
	{
		if (imageData[i] == color->r && imageData[i + 1] == color->g && imageData[i + 2] == color->b)
		{
			imageData[i + 3] = 0;
		}
	}
}

void TextureLoader::Colorize(ILubyte *imageData, int size, Color *color)
{
	for (int i = 0; i < size * 4; i += 4)
	{
		int rr = (int(imageData[i]) * int(color->r)) >> 8;
		int rg = (int(imageData[i + 1]) * int(color->g)) >> 8;
		int rb = (int(imageData[i + 2]) * int(color->b)) >> 8;
		int fak = int(imageData[i]) * 5 - 4 * 256 - 138;

		if (fak > 0)
		{
			rr += fak;
			rg += fak;
			rb += fak;
		}

		rr = rr < 255 ? rr : 255;
		rg = rg < 255 ? rg : 255;
		rb = rb < 255 ? rb : 255;

		imageData[i] = rr > 0 ? (GLubyte) rr : 1;
		imageData[i + 1] = rg > 0 ? (GLubyte) rg : 1;
		imageData[i + 2] = rb > 0 ? (GLubyte) rb : 1;
	}
}
