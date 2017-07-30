#include "OpenGLTextureManager.h"

OpenGLTextureManager::OpenGLTextureManager()
{
}

OpenGLTextureManager::~OpenGLTextureManager()
{
	for (auto texture : Textures)
	{
		delete texture;
	}
}

Texture* OpenGLTextureManager::Load(const char* path)
{
	auto texture = new OpenGLTexture(path);
	Textures.push_back(texture);
	return texture;
}
