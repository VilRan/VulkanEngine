#pragma once

#include <stb_image.h>

class Texture
{
public:
	Texture(stbi_uc* pixels, int width, int height, int channels);
	virtual ~Texture();

	inline const stbi_uc* GetPixels() const { return Pixels; }
	inline const int GetWidth() const { return Width; }
	inline const int GetHeight() const { return Height; }
	inline const int GetChannels() const { return Channels; }

private:
	stbi_uc* Pixels;
	int Width, Height, Channels;
};