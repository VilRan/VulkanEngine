#include "Texture.h"

Texture::Texture(stbi_uc* pixels, int width, int height, int channels)
{
	Pixels = pixels;
	Width = width;
	Height = height;
	Channels = channels;
}

Texture::~Texture()
{
	stbi_image_free(Pixels);
}
