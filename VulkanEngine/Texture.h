#pragma once

#include <stb_image.h>

class Texture
{
public:
	Texture();
	virtual ~Texture();

	inline const int GetWidth() const { return Width; }
	inline const int GetHeight() const { return Height; }
	inline const int GetChannels() const { return Channels; }

protected:
	int Width, Height, Channels;
};