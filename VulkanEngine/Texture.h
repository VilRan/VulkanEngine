#pragma once

#include <stb_image.h>

class Texture
{
public:
	Texture(stbi_uc* pixels, int width, int height, int channels);
	virtual ~Texture();

	stbi_uc* Pixels;
	int Width, Height, Channels;
};