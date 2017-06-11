#pragma once

#include <stb_image.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	const int GetWidth() const { return Width; }
	const int GetHeight() const { return Height; }
	const int GetChannels() const { return Channels; }

protected:
	int Width, Height, Channels;
};