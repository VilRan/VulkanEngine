#include "OpenGLTexture.h"

#include <stb_image.h>
#include <stdexcept>

OpenGLTexture::OpenGLTexture(const char* path)
{
	stbi_uc* pixels = stbi_load(path, &Width, &Height, &Channels, STBI_rgb);
	if (!pixels)
	{
		throw std::runtime_error("Failed to load texture image!");
	}

	glGenTextures(1, &Index);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Index);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, Width, Height, 0, GL_RGB, GL_UNSIGNED_BYTE, pixels);
	glGenerateMipmap(GL_TEXTURE_2D);

	stbi_image_free(pixels);
}

OpenGLTexture::~OpenGLTexture()
{
	glDeleteTextures(1, &Index);
}

void OpenGLTexture::Bind()
{
	//glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, Index);
}
