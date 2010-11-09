#include "Image.h"
#include "../Debug.h"
Image::Image()
{
	ilGenImages(1, &this->imageId);
}

Image::~Image()
{
	ilDeleteImage(this->imageId);
}

ILint Image::getWidth()
{
	return ilGetInteger(IL_IMAGE_WIDTH);
}

ILint Image::getHeight()
{
	return ilGetInteger(IL_IMAGE_HEIGHT);
}

ILint Image::getDepth()
{
	return ilGetInteger(IL_IMAGE_DEPTH);
}

ILint Image::getBpp()
{
	return ilGetInteger(IL_IMAGE_BPP);
}

ILint Image::getFormat()
{
	return ilGetInteger(IL_IMAGE_FORMAT);
}

ILubyte* Image::getData()
{
	ILubyte *imageData = ilGetData();
	if (!imageData) {
		ILenum error;
		while ((error = ilGetError()) != IL_NO_ERROR) {
			wcout << error << L" " << iluErrorString(error);
		}
		return 0;
	}
	return imageData;
}

bool Image::loadFromFile(wchar_t *filename)
{
	// Load the image from file.
	ILboolean retval = ilLoadImage(filename);
	if (!retval) {
		ILenum error;
		while ((error = ilGetError()) != IL_NO_ERROR) {
			wcout << error << L" " << iluErrorString(error);
		}
		return false;
	}
	return true;
}

bool Image::convert()
{
	ILboolean retval = ilConvertImage(IL_RGBA, IL_UNSIGNED_BYTE);
	if (!retval) {
		ILenum error;
		while ((error = ilGetError()) != IL_NO_ERROR) {
			wcout << error << L" " << iluErrorString(error);
		}
		return false;
	}
	return true;
}

bool Image::scale(ILint width, ILint height, ILint depth)
{
	ILboolean retval = iluScale(width, height, depth);
	if (!retval) {
		ILenum error;
		while ((error = ilGetError()) != IL_NO_ERROR) {
			wcout << error << L" " << iluErrorString(error);
		}
		return false;
	}
	return true;
}

void Image::bind()
{
	ilBindImage(this->imageId);
}